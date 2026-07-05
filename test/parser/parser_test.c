/* ************************************************************************** */
/*                                                                            */
/*   parser_test.c                                                            */
/*   Suite de testes para os parsers do miniRT.                               */
/*   Cobre todos os erros definidos em definitions.h, testando retorno (0/1)  */
/*   e a mensagem exata impressa em stdout via captura com pipe().            */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <string.h>
#include <unistd.h>

/* ===================================================================== */
/*  PALETA / FORMATAÇÃO (igual ao algelin_test.c)                        */
/* ===================================================================== */
#define GREEN  "\033[0;32m"
#define RED    "\033[0;31m"
#define CYAN   "\033[0;36m"
#define RESET  "\033[0m"
#define BOLD   "\033[1m"

/* ===================================================================== */
/*  CONTADORES GLOBAIS                                                    */
/* ===================================================================== */
static int	g_passed = 0;
static int	g_failed = 0;

/* ===================================================================== */
/*  INFRA DE CAPTURA DE STDOUT                                           */
/* ===================================================================== */

/*
** Redireciona stdout para a extremidade de escrita de um pipe.
** Retorna o fd original de stdout (salvo via dup) para restauração.
*/
static int	capture_begin(int pipe_fd[2])
{
	int	saved_stdout;

	pipe(pipe_fd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	return (saved_stdout);
}

/*
** Restaura stdout e lê tudo que foi escrito no pipe para 'buf' (max len-1).
** Garante terminação em '\0' e remove o '\n' final se houver.
*/
static void	capture_end(int pipe_fd[2], int saved_stdout,
							char *buf, size_t len)
{
	ssize_t	n;

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	n = read(pipe_fd[0], buf, len - 1);
	close(pipe_fd[0]);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	/* remove newline final para comparação limpa */
	if (n > 0 && buf[n - 1] == '\n')
		buf[n - 1] = '\0';
}

/* ===================================================================== */
/*  HELPERS DE ASSERT                                                     */
/* ===================================================================== */

static void	check_return(const char *test, int got, int expected)
{
	if (got == expected)
	{
		printf(GREEN "  [PASS]" RESET " %s → retorno %d\n", test, got);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %s → retorno %d, esperado %d\n",
			test, got, expected);
		g_failed++;
	}
}

static void	check_msg(const char *test, const char *got, const char *expected)
{
	if (strcmp(got, expected) == 0)
	{
		printf(GREEN "  [PASS]" RESET " %s\n", test);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %s\n", test);
		printf("         got      → \"%s\"\n", got);
		printf("         esperado → \"%s\"\n", expected);
		g_failed++;
	}
}

static void	print_header(const char *title)
{
	printf("\n" BOLD CYAN
		"════════════════════════════════════════════\n"
		"  %s\n"
		"════════════════════════════════════════════"
		RESET "\n", title);
}

/* ===================================================================== */
/*  MACRO: testa retorno + mensagem em uma única chamada                 */
/*                                                                       */
/*  Uso:                                                                 */
/*    RUN(label, expected_ret, expected_msg, fn_call);                   */
/* ===================================================================== */
#define RUN(label, exp_ret, exp_msg, call) \
do { \
	int		_pfd[2]; \
	char	_buf[512]; \
	char	_lbl[256]; \
	int	_saved = capture_begin(_pfd); \
	int	_ret   = (call); \
	capture_end(_pfd, _saved, _buf, sizeof(_buf)); \
	snprintf(_lbl, sizeof(_lbl), "%s (retorno)", (label)); \
	check_return(_lbl, _ret, (exp_ret)); \
	if ((exp_msg) != NULL) { \
		snprintf(_lbl, sizeof(_lbl), "%s (mensagem)", (label)); \
		check_msg(_lbl, _buf, (exp_msg)); \
	} \
} while (0)

/* ===================================================================== */
/*  FÁBRICA DE t_scene LIMPA                                             */
/* ===================================================================== */
static t_scene	*new_scene(void)
{
	return (ft_calloc(1, sizeof(t_scene)));
}

/* ===================================================================== */
/*  HELPERS: monta arrays de strings (params) como os parsers recebem   */
/* ===================================================================== */

/*
** Retorna um array de strings terminado em NULL, como ft_strsplit_any devolveria.
** Os ponteiros apontam para literais — não libere individualmente.
*/
static char	**make_params(const char *p0, const char *p1,
							const char *p2, const char *p3,
							const char *p4, const char *p5)
{
	static char	*arr[7];
	int			i;

	i = 0;
	arr[i++] = (char *)p0;
	if (p1) arr[i++] = (char *)p1;
	if (p2) arr[i++] = (char *)p2;
	if (p3) arr[i++] = (char *)p3;
	if (p4) arr[i++] = (char *)p4;
	if (p5) arr[i++] = (char *)p5;
	arr[i] = NULL;
	return (arr);
}

/* ===================================================================== */
/*  SEÇÃO 1 — print_error: todas as mensagens definidas em definitions.h */
/* ===================================================================== */

/*
** Formato produzido por print_error():
**   "miniRT: <obj_name>: <error_msg> (line <n>)"
** Testamos linha 0 (como usado no código).
*/
static void	test_print_error_all_messages(void)
{
	int		pfd[2];
	char	buf[512];
	int		saved;

	print_header("print_error — cobertura de todos os enums");

	/* Macro local para não repetir boilerplate */
#define CHECK_ERR(label, obj, opt, expected) \
	saved = capture_begin(pfd); \
	print_error((obj), (opt), 0); \
	capture_end(pfd, saved, buf, sizeof(buf)); \
	check_msg((label), buf, (expected));

	CHECK_ERR("ERR_NO_INFORMATION / Ambient",
		OBJ_AMBIENT, ERR_NO_INFORMATION,
		"miniRT: Ambient lighting: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_INFORMATION / Camera",
		OBJ_CAMERA, ERR_NO_INFORMATION,
		"miniRT: Camera: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_INFORMATION / Light",
		OBJ_LIGHT, ERR_NO_INFORMATION,
		"miniRT: Light: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_INFORMATION / Sphere",
		OBJ_SPHERE, ERR_NO_INFORMATION,
		"miniRT: Sphere: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_INFORMATION / Plane",
		OBJ_PLANE, ERR_NO_INFORMATION,
		"miniRT: Plane: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_INFORMATION / Cylinder",
		OBJ_CYLINDER, ERR_NO_INFORMATION,
		"miniRT: Cylinder: don`t have all the specific information (line 0)");

	CHECK_ERR("ERR_NO_OBJECT",
		OBJ_SPHERE, ERR_NO_OBJECT,
		"miniRT: Sphere: missing object declaration in scene file (line 0)");

	CHECK_ERR("ERR_NO_UNIQUE / Ambient",
		OBJ_AMBIENT, ERR_NO_UNIQUE,
		"miniRT: Ambient lighting: not a unique object in scene (line 0)");

	CHECK_ERR("ERR_NO_UNIQUE / Camera",
		OBJ_CAMERA, ERR_NO_UNIQUE,
		"miniRT: Camera: not a unique object in scene (line 0)");

	CHECK_ERR("ERR_NO_UNIQUE / Light",
		OBJ_LIGHT, ERR_NO_UNIQUE,
		"miniRT: Light: not a unique object in scene (line 0)");

	CHECK_ERR("ERR_NO_PARAM_RATIO",
		OBJ_AMBIENT, ERR_NO_PARAM_RATIO,
		"miniRT: Ambient lighting: missing ratio parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_COLOR / Sphere",
		OBJ_SPHERE, ERR_NO_PARAM_COLOR,
		"miniRT: Sphere: missing color parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_COLOR / Camera",
		OBJ_CAMERA, ERR_NO_PARAM_COLOR,
		"miniRT: Camera: missing color parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_COORDS / Camera",
		OBJ_CAMERA, ERR_NO_PARAM_COORDS,
		"miniRT: Camera: missing coordinates parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_COORDS / Plane",
		OBJ_PLANE, ERR_NO_PARAM_COORDS,
		"miniRT: Plane: missing coordinates parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_VEC / Cylinder",
		OBJ_CYLINDER, ERR_NO_PARAM_VEC,
		"miniRT: Cylinder: missing orientation vector parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_VEC / Plane",
		OBJ_PLANE, ERR_NO_PARAM_VEC,
		"miniRT: Plane: missing orientation vector parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_DIAMETER",
		OBJ_SPHERE, ERR_NO_PARAM_DIAMETER,
		"miniRT: Sphere: missing diameter parameter (line 0)");

	CHECK_ERR("ERR_NO_PARAM_HEIGHT",
		OBJ_CYLINDER, ERR_NO_PARAM_HEIGHT,
		"miniRT: Cylinder: missing height parameter (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_FOV",
		OBJ_CAMERA, ERR_OUT_RANGE_FOV,
		"miniRT: Camera: fov out of range [0, 180] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_RATIO",
		OBJ_AMBIENT, ERR_OUT_RANGE_RATIO,
		"miniRT: Ambient lighting: ratio out of range [0.0, 1.0] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_BRIGHT",
		OBJ_LIGHT, ERR_OUT_RANGE_BRIGHT,
		"miniRT: Light: brightness out of range [0.0,1.0] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_COLOR / Sphere",
		OBJ_SPHERE, ERR_OUT_RANGE_COLOR,
		"miniRT: Sphere: color value out of range [0-255] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_COLOR / Cylinder",
		OBJ_CYLINDER, ERR_OUT_RANGE_COLOR,
		"miniRT: Cylinder: color value out of range [0-255] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_VEC / Camera",
		OBJ_CAMERA, ERR_OUT_RANGE_VEC,
		"miniRT: Camera: normalized vector value out of range [-1, 1] (line 0)");

	CHECK_ERR("ERR_OUT_RANGE_VEC / Plane",
		OBJ_PLANE, ERR_OUT_RANGE_VEC,
		"miniRT: Plane: normalized vector value out of range [-1, 1] (line 0)");

	CHECK_ERR("ERR_COORDS_INVALID",
		OBJ_CAMERA, ERR_COORDS_INVALID,
		"miniRT: Camera: invalid coordinates value (line 0)");

	CHECK_ERR("ERR_DIAMETER_NEGATIVE / Sphere",
		OBJ_SPHERE, ERR_DIAMETER_NEGATIVE,
		"miniRT: Sphere: diameter value negative (line 0)");

	CHECK_ERR("ERR_DIAMETER_NEGATIVE / Cylinder",
		OBJ_CYLINDER, ERR_DIAMETER_NEGATIVE,
		"miniRT: Cylinder: diameter value negative (line 0)");

#undef CHECK_ERR
}

/* ===================================================================== */
/*  SEÇÃO 2 — fill_color                                                 */
/* ===================================================================== */
static void	test_fill_color(void)
{
	t_color	c;
	char	**p;

	print_header("fill_color");

	/* --- Caso feliz: cor válida --- */
	p = make_params("255,128,0", NULL, NULL, NULL, NULL, NULL);
	RUN("cor válida 255,128,0 — retorno 0", 0, NULL,
		fill_color(p[0], &c, OBJ_SPHERE));
	/* verifica valores normalizados */
	{
		int ok = (fabs(c.red - 1.0) < 1e-9
			&& fabs(c.green - (128.0/255.0)) < 1e-9
			&& fabs(c.blue - 0.0) < 1e-9);
		if (ok) { printf(GREEN "  [PASS]" RESET " valores normalizados corretos\n"); g_passed++; }
		else    { printf(RED "  [FAIL]" RESET " valores normalizados incorretos"
			" (r=%.4f g=%.4f b=%.4f)\n", c.red, c.green, c.blue); g_failed++; }
	}

	/* --- Caso feliz: preto --- */
	p = make_params("0,0,0", NULL, NULL, NULL, NULL, NULL);
	RUN("cor preta 0,0,0 — retorno 0", 0, NULL,
		fill_color(p[0], &c, OBJ_PLANE));

	/* --- Caso feliz: branco --- */
	p = make_params("255,255,255", NULL, NULL, NULL, NULL, NULL);
	RUN("cor branca 255,255,255 — retorno 0", 0, NULL,
		fill_color(p[0], &c, OBJ_CYLINDER));

	/* --- ERR_NO_PARAM_COLOR: menos de 3 componentes --- */
	RUN("ERR_NO_PARAM_COLOR: '255,128' (só 2) — retorno 1", 1,
		"miniRT: Sphere: missing color parameter (line 0)",
		fill_color("255,128", &c, OBJ_SPHERE));

	RUN("ERR_NO_PARAM_COLOR: '255' (só 1) — retorno 1", 1,
		"miniRT: Camera: missing color parameter (line 0)",
		fill_color("255", &c, OBJ_CAMERA));

	RUN("ERR_NO_PARAM_COLOR: '' (vazio) — retorno 1", 1,
		"miniRT: Light: missing color parameter (line 0)",
		fill_color("", &c, OBJ_LIGHT));

	/* --- ERR_NO_PARAM_COLOR: mais de 3 componentes --- */
	RUN("ERR_NO_PARAM_COLOR: '255,0,0,1' (4 componentes) — retorno 1", 1,
		"miniRT: Plane: missing color parameter (line 0)",
		fill_color("255,0,0,1", &c, OBJ_PLANE));

	/* --- ERR_OUT_RANGE_COLOR: vermelho > 255 --- */
	RUN("ERR_OUT_RANGE_COLOR: '256,0,0' — retorno 1", 1,
		"miniRT: Sphere: color value out of range [0-255] (line 0)",
		fill_color("256,0,0", &c, OBJ_SPHERE));

	/* --- ERR_OUT_RANGE_COLOR: verde < 0 --- */
	RUN("ERR_OUT_RANGE_COLOR: '0,-1,0' — retorno 1", 1,
		"miniRT: Cylinder: color value out of range [0-255] (line 0)",
		fill_color("0,-1,0", &c, OBJ_CYLINDER));

	/* --- ERR_OUT_RANGE_COLOR: azul > 255 --- */
	RUN("ERR_OUT_RANGE_COLOR: '0,0,300' — retorno 1", 1,
		"miniRT: Ambient lighting: color value out of range [0-255] (line 0)",
		fill_color("0,0,300", &c, OBJ_AMBIENT));
}

/* ===================================================================== */
/*  SEÇÃO 3 — fill_coordinate                                            */
/* ===================================================================== */
static void	test_fill_coordinate(void)
{
	t_point	pt;

	print_header("fill_coordinate");

	/* --- Caso feliz --- */
	RUN("coordenada válida '1.0,2.5,-3.0' — retorno 0", 0, NULL,
		fill_coordinate("1.0,2.5,-3.0", &pt, OBJ_SPHERE));
	{
		int ok = (fabs(pt.x - 1.0) < 1e-9
			&& fabs(pt.y - 2.5) < 1e-9
			&& fabs(pt.z + 3.0) < 1e-9);
		if (ok) { printf(GREEN "  [PASS]" RESET " valores x/y/z corretos\n"); g_passed++; }
		else    { printf(RED "  [FAIL]" RESET " valores incorretos"
			" (x=%.4f y=%.4f z=%.4f)\n", pt.x, pt.y, pt.z); g_failed++; }
	}

	/* --- Caso feliz: coordenadas zero --- */
	RUN("coordenada '0,0,0' — retorno 0", 0, NULL,
		fill_coordinate("0,0,0", &pt, OBJ_CAMERA));

	/* --- Caso feliz: valores grandes --- */
	RUN("coordenada '1000.5,-999.9,0.001' — retorno 0", 0, NULL,
		fill_coordinate("1000.5,-999.9,0.001", &pt, OBJ_LIGHT));

	/* --- ERR_NO_PARAM_COORDS: menos de 3 componentes --- */
	RUN("ERR_NO_PARAM_COORDS: '1.0,2.0' — retorno 1", 1,
		"miniRT: Camera: missing coordinates parameter (line 0)",
		fill_coordinate("1.0,2.0", &pt, OBJ_CAMERA));

	RUN("ERR_NO_PARAM_COORDS: '1.0' — retorno 1", 1,
		"miniRT: Sphere: missing coordinates parameter (line 0)",
		fill_coordinate("1.0", &pt, OBJ_SPHERE));

	RUN("ERR_NO_PARAM_COORDS: '' — retorno 1", 1,
		"miniRT: Plane: missing coordinates parameter (line 0)",
		fill_coordinate("", &pt, OBJ_PLANE));

	/* --- ERR_NO_PARAM_COORDS: mais de 3 componentes --- */
	RUN("ERR_NO_PARAM_COORDS: '1,2,3,4' — retorno 1", 1,
		"miniRT: Light: missing coordinates parameter (line 0)",
		fill_coordinate("1,2,3,4", &pt, OBJ_LIGHT));
}

/* ===================================================================== */
/*  SEÇÃO 4 — fill_normalized                                            */
/* ===================================================================== */
static void	test_fill_normalized(void)
{
	t_point	pt;

	print_header("fill_normalized");

	/* --- Caso feliz: eixos canônicos --- */
	RUN("vetor '1,0,0' — retorno 0", 0, NULL,
		fill_normalized("1,0,0", &pt, OBJ_CAMERA));
	RUN("vetor '0,1,0' — retorno 0", 0, NULL,
		fill_normalized("0,1,0", &pt, OBJ_PLANE));
	RUN("vetor '0,0,-1' — retorno 0", 0, NULL,
		fill_normalized("0,0,-1", &pt, OBJ_CYLINDER));

	/* --- Caso feliz: diagonal unitária --- */
	RUN("vetor '0.577,0.577,0.577' — retorno 0", 0, NULL,
		fill_normalized("0.577,0.577,0.577", &pt, OBJ_CAMERA));

	/* --- Caso feliz: limite exato [-1, 1] --- */
	RUN("vetor '-1,-1,-1' (limite inferior) — retorno 0", 0, NULL,
		fill_normalized("-1,-1,-1", &pt, OBJ_PLANE));
	RUN("vetor '1,1,1' (limite superior) — retorno 0", 0, NULL,
		fill_normalized("1,1,1", &pt, OBJ_CAMERA));

	/* --- ERR_NO_PARAM_VEC: componentes faltando --- */
	RUN("ERR_NO_PARAM_VEC: '1,0' — retorno 1", 1,
		"miniRT: Camera: missing orientation vector parameter (line 0)",
		fill_normalized("1,0", &pt, OBJ_CAMERA));

	RUN("ERR_NO_PARAM_VEC: '' — retorno 1", 1,
		"miniRT: Plane: missing orientation vector parameter (line 0)",
		fill_normalized("", &pt, OBJ_PLANE));

	RUN("ERR_NO_PARAM_VEC: '1,0,0,0' (4 componentes) — retorno 1", 1,
		"miniRT: Cylinder: missing orientation vector parameter (line 0)",
		fill_normalized("1,0,0,0", &pt, OBJ_CYLINDER));

	/* --- ERR_OUT_RANGE_VEC: x fora de [-1,1] --- */
	RUN("ERR_OUT_RANGE_VEC: '1.1,0,0' — retorno 1", 1,
		"miniRT: Camera: normalized vector value out of range [-1, 1] (line 0)",
		fill_normalized("1.1,0,0", &pt, OBJ_CAMERA));

	RUN("ERR_OUT_RANGE_VEC: '-1.5,0,0' — retorno 1", 1,
		"miniRT: Plane: normalized vector value out of range [-1, 1] (line 0)",
		fill_normalized("-1.5,0,0", &pt, OBJ_PLANE));

	/* --- ERR_OUT_RANGE_VEC: y fora de [-1,1] --- */
	RUN("ERR_OUT_RANGE_VEC: '0,2,0' — retorno 1", 1,
		"miniRT: Cylinder: normalized vector value out of range [-1, 1] (line 0)",
		fill_normalized("0,2,0", &pt, OBJ_CYLINDER));

	/* --- ERR_OUT_RANGE_VEC: z fora de [-1,1] --- */
	RUN("ERR_OUT_RANGE_VEC: '0,0,1.001' — retorno 1", 1,
		"miniRT: Camera: normalized vector value out of range [-1, 1] (line 0)",
		fill_normalized("0,0,1.001", &pt, OBJ_CAMERA));
}

/* ===================================================================== */
/*  SEÇÃO 5 — amb_light_parser (ERR_NO_UNIQUE, ERR_NO_INFORMATION,      */
/*             ERR_OUT_RANGE_RATIO, ERR_NO_PARAM_COLOR, caminho feliz)   */
/* ===================================================================== */
static void	test_amb_light_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("amb_light_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("A", "0.5", "255,255,255", NULL, NULL, NULL);
	RUN("ambient válido 'A 0.5 255,255,255' — retorno 0", 0, NULL,
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- Caso feliz: ratio nos limites --- */
	sc = new_scene();
	p = make_params("A", "0.0", "0,0,0", NULL, NULL, NULL);
	RUN("ambient ratio=0.0 — retorno 0", 0, NULL,
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	sc = new_scene();
	p = make_params("A", "1.0", "255,255,255", NULL, NULL, NULL);
	RUN("ambient ratio=1.0 — retorno 0", 0, NULL,
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_UNIQUE: segunda declaração de ambient --- */
	sc = new_scene();
	p = make_params("A", "0.5", "255,255,255", NULL, NULL, NULL);
	amb_light_parser(p, sc);          /* primeira — deve ter sucesso */
	RUN("ERR_NO_UNIQUE: segundo ambient — retorno 1", 1,
		"miniRT: Ambient lighting: not a unique object in scene (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: parâmetros insuficientes --- */
	sc = new_scene();
	p = make_params("A", "0.5", NULL, NULL, NULL, NULL);
	RUN("ERR_NO_INFORMATION: só 2 params — retorno 1", 1,
		"miniRT: Ambient lighting: don`t have all the specific information (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: parâmetros em excesso --- */
	sc = new_scene();
	p = make_params("A", "0.5", "255,0,0", "extra", NULL, NULL);
	RUN("ERR_NO_INFORMATION: 4 params — retorno 1", 1,
		"miniRT: Ambient lighting: don`t have all the specific information (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_RATIO: ratio > 1.0 --- */
	sc = new_scene();
	p = make_params("A", "1.5", "255,255,255", NULL, NULL, NULL);
	RUN("ERR_OUT_RANGE_RATIO: ratio=1.5 — retorno 1", 1,
		"miniRT: Ambient lighting: ratio out of range [0.0, 1.0] (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_RATIO: ratio < 0.0 --- */
	sc = new_scene();
	p = make_params("A", "-0.1", "255,255,255", NULL, NULL, NULL);
	RUN("ERR_OUT_RANGE_RATIO: ratio=-0.1 — retorno 1", 1,
		"miniRT: Ambient lighting: ratio out of range [0.0, 1.0] (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COLOR: cor malformada --- */
	sc = new_scene();
	p = make_params("A", "0.5", "255,255", NULL, NULL, NULL);
	RUN("ERR_NO_PARAM_COLOR via ambient — retorno 1", 1,
		"miniRT: Ambient lighting: missing color parameter (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_COLOR via ambient --- */
	sc = new_scene();
	p = make_params("A", "0.5", "256,0,0", NULL, NULL, NULL);
	RUN("ERR_OUT_RANGE_COLOR via ambient — retorno 1", 1,
		"miniRT: Ambient lighting: color value out of range [0-255] (line 0)",
		amb_light_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 6 — cam_parser                                                 */
/* ===================================================================== */
static void	test_cam_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("cam_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "90", NULL, NULL);
	RUN("câmera válida — retorno 0", 0, NULL,
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- Caso feliz: FOV nos limites --- */
	sc = new_scene();
	p = make_params("C", "1,2,3", "0,0,-1", "0", NULL, NULL);
	RUN("câmera fov=0 — retorno 0", 0, NULL,
		cam_parser(p, sc));
	free_scene_obj(&sc);

	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "180", NULL, NULL);
	RUN("câmera fov=180 — retorno 0", 0, NULL,
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_UNIQUE --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "90", NULL, NULL);
	cam_parser(p, sc);
	RUN("ERR_NO_UNIQUE: segunda câmera — retorno 1", 1,
		"miniRT: Camera: not a unique object in scene (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: parâmetros insuficientes --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", NULL, NULL, NULL);
	RUN("ERR_NO_INFORMATION: 3 params — retorno 1", 1,
		"miniRT: Camera: don`t have all the specific information (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: parâmetros em excesso --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "90", "extra", NULL);
	RUN("ERR_NO_INFORMATION: 5 params — retorno 1", 1,
		"miniRT: Camera: don`t have all the specific information (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_FOV: fov > 180 --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "181", NULL, NULL);
	RUN("ERR_OUT_RANGE_FOV: fov=181 — retorno 1", 1,
		"miniRT: Camera: fov out of range [0, 180] (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_FOV: fov < 0 --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1,0", "-1", NULL, NULL);
	RUN("ERR_OUT_RANGE_FOV: fov=-1 — retorno 1", 1,
		"miniRT: Camera: fov out of range [0, 180] (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COORDS via câmera --- */
	sc = new_scene();
	p = make_params("C", "0,0", "0,1,0", "90", NULL, NULL);
	RUN("ERR_NO_PARAM_COORDS via câmera — retorno 1", 1,
		"miniRT: Camera: missing coordinates parameter (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_VEC via câmera --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,1", "90", NULL, NULL);
	RUN("ERR_NO_PARAM_VEC via câmera — retorno 1", 1,
		"miniRT: Camera: missing orientation vector parameter (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_VEC via câmera --- */
	sc = new_scene();
	p = make_params("C", "0,0,0", "0,2,0", "90", NULL, NULL);
	RUN("ERR_OUT_RANGE_VEC via câmera — retorno 1", 1,
		"miniRT: Camera: normalized vector value out of range [-1, 1] (line 0)",
		cam_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 7 — light_parser                                               */
/* ===================================================================== */
static void	test_light_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("light_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "0.8", "255,255,255", NULL, NULL);
	RUN("light válida — retorno 0", 0, NULL,
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- Caso feliz: brightness nos limites --- */
	sc = new_scene();
	p = make_params("L", "0,0,0", "0.0", "0,0,0", NULL, NULL);
	RUN("light brightness=0.0 — retorno 0", 0, NULL,
		light_parser(p, sc));
	free_scene_obj(&sc);

	sc = new_scene();
	p = make_params("L", "0,0,0", "1.0", "255,255,255", NULL, NULL);
	RUN("light brightness=1.0 — retorno 0", 0, NULL,
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_UNIQUE --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "0.8", "255,255,255", NULL, NULL);
	light_parser(p, sc);
	RUN("ERR_NO_UNIQUE: segunda light — retorno 1", 1,
		"miniRT: Light: not a unique object in scene (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "0.8", NULL, NULL, NULL);
	RUN("ERR_NO_INFORMATION: 3 params — retorno 1", 1,
		"miniRT: Light: don`t have all the specific information (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_BRIGHT: > 1.0 --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "1.1", "255,255,255", NULL, NULL);
	RUN("ERR_OUT_RANGE_BRIGHT: 1.1 — retorno 1", 1,
		"miniRT: Light: brightness out of range [0.0,1.0] (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_BRIGHT: < 0.0 --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "-0.5", "255,255,255", NULL, NULL);
	RUN("ERR_OUT_RANGE_BRIGHT: -0.5 — retorno 1", 1,
		"miniRT: Light: brightness out of range [0.0,1.0] (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COORDS via light --- */
	sc = new_scene();
	p = make_params("L", "0,5", "0.8", "255,255,255", NULL, NULL);
	RUN("ERR_NO_PARAM_COORDS via light — retorno 1", 1,
		"miniRT: Light: missing coordinates parameter (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COLOR via light --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "0.8", "255,255", NULL, NULL);
	RUN("ERR_NO_PARAM_COLOR via light — retorno 1", 1,
		"miniRT: Light: missing color parameter (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_COLOR via light --- */
	sc = new_scene();
	p = make_params("L", "0,5,0", "0.8", "256,0,0", NULL, NULL);
	RUN("ERR_OUT_RANGE_COLOR via light — retorno 1", 1,
		"miniRT: Light: color value out of range [0-255] (line 0)",
		light_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 8 — sphere_parser                                              */
/* ===================================================================== */
static void	test_sphere_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("sphere_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "2.0", "255,0,0", NULL, NULL);
	RUN("esfera válida — retorno 0", 0, NULL,
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- Caso feliz: múltiplas esferas na cena --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "1.0", "255,0,0", NULL, NULL);
	sphere_parser(p, sc);
	p = make_params("sp", "5,0,0", "2.0", "0,255,0", NULL, NULL);
	RUN("segunda esfera na mesma cena — retorno 0", 0, NULL,
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: menos de 4 params --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "2.0", NULL, NULL, NULL);
	RUN("ERR_NO_INFORMATION: 3 params — retorno 1", 1,
		"miniRT: Sphere: don`t have all the specific information (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: mais de 4 params --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "2.0", "255,0,0", "extra", NULL);
	RUN("ERR_NO_INFORMATION: 5 params — retorno 1", 1,
		"miniRT: Sphere: don`t have all the specific information (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_DIAMETER_NEGATIVE: diâmetro zero --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "0.0", "255,0,0", NULL, NULL);
	RUN("ERR_DIAMETER_NEGATIVE: diam=0.0 — retorno 1", 1,
		"miniRT: Sphere: diameter value negative (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_DIAMETER_NEGATIVE: diâmetro negativo --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "-1.0", "255,0,0", NULL, NULL);
	RUN("ERR_DIAMETER_NEGATIVE: diam=-1.0 — retorno 1", 1,
		"miniRT: Sphere: diameter value negative (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COORDS via esfera --- */
	sc = new_scene();
	p = make_params("sp", "0,0", "2.0", "255,0,0", NULL, NULL);
	RUN("ERR_NO_PARAM_COORDS via esfera — retorno 1", 1,
		"miniRT: Sphere: missing coordinates parameter (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COLOR via esfera --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "2.0", "255,0", NULL, NULL);
	RUN("ERR_NO_PARAM_COLOR via esfera — retorno 1", 1,
		"miniRT: Sphere: missing color parameter (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_COLOR via esfera --- */
	sc = new_scene();
	p = make_params("sp", "0,0,0", "2.0", "256,0,0", NULL, NULL);
	RUN("ERR_OUT_RANGE_COLOR via esfera — retorno 1", 1,
		"miniRT: Sphere: color value out of range [0-255] (line 0)",
		sphere_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 9 — plane_parser                                               */
/* ===================================================================== */
static void	test_plane_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("plane_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1,0", "100,200,50", NULL, NULL);
	RUN("plano válido — retorno 0", 0, NULL,
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1,0", NULL, NULL, NULL);
	RUN("ERR_NO_INFORMATION: 3 params — retorno 1", 1,
		"miniRT: Plane: don`t have all the specific information (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COORDS via plano --- */
	sc = new_scene();
	p = make_params("pl", "0,0", "0,1,0", "100,200,50", NULL, NULL);
	RUN("ERR_NO_PARAM_COORDS via plano — retorno 1", 1,
		"miniRT: Plane: missing coordinates parameter (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_VEC via plano --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1", "100,200,50", NULL, NULL);
	RUN("ERR_NO_PARAM_VEC via plano — retorno 1", 1,
		"miniRT: Plane: missing orientation vector parameter (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_VEC via plano --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1.5,0", "100,200,50", NULL, NULL);
	RUN("ERR_OUT_RANGE_VEC via plano — retorno 1", 1,
		"miniRT: Plane: normalized vector value out of range [-1, 1] (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COLOR via plano --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1,0", "100,200", NULL, NULL);
	RUN("ERR_NO_PARAM_COLOR via plano — retorno 1", 1,
		"miniRT: Plane: missing color parameter (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_COLOR via plano --- */
	sc = new_scene();
	p = make_params("pl", "0,0,0", "0,1,0", "256,200,50", NULL, NULL);
	RUN("ERR_OUT_RANGE_COLOR via plano — retorno 1", 1,
		"miniRT: Plane: color value out of range [0-255] (line 0)",
		plane_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 10 — cilinder_parser                                           */
/* ===================================================================== */
static void	test_cilinder_parser(void)
{
	t_scene	*sc;
	char	**p;

	print_header("cilinder_parser");

	/* --- Caso feliz --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", "255,0,255");
	RUN("cilindro válido — retorno 0", 0, NULL,
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: menos de 6 params --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", NULL);
	RUN("ERR_NO_INFORMATION: 5 params — retorno 1", 1, NULL,
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_INFORMATION: mais de 6 params --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", "0,0,0");
	/* adiciona extra manualmente via array estático local */
	{
		static char	*arr7[8] = {"cy","0,0,0","0,1,0","2.0","5.0","0,0,0","extra",NULL};
		t_scene *sc2 = new_scene();
		RUN("ERR_NO_INFORMATION: 7 params — retorno 1", 1, NULL,
			cilinder_parser(arr7, sc2));
		free_scene_obj(&sc2);
	}
	free_scene_obj(&sc);

	/* --- ERR_DIAMETER_NEGATIVE: diâmetro = 0 --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "0.0", "5.0", "255,0,0");
	RUN("ERR_DIAMETER_NEGATIVE: diam=0 — retorno 1", 1,
		"miniRT: Cylinder: diameter value negative (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_DIAMETER_NEGATIVE: diâmetro negativo --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "-3.0", "5.0", "255,0,0");
	RUN("ERR_DIAMETER_NEGATIVE: diam=-3 — retorno 1", 1,
		"miniRT: Cylinder: diameter value negative (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_HEIGHT: altura = 0 --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "0.0", "255,0,0");
	RUN("ERR_NO_PARAM_HEIGHT: height=0 — retorno 1", 1,
		"miniRT: Cylinder: missing height parameter (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_HEIGHT: altura negativa --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "-2.0", "255,0,0");
	RUN("ERR_NO_PARAM_HEIGHT: height=-2 — retorno 1", 1,
		"miniRT: Cylinder: missing height parameter (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COORDS via cilindro --- */
	sc = new_scene();
	p = make_params("cy", "0,0", "0,1,0", "2.0", "5.0", "255,0,0");
	RUN("ERR_NO_PARAM_COORDS via cilindro — retorno 1", 1,
		"miniRT: Cylinder: missing coordinates parameter (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_VEC via cilindro --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1", "2.0", "5.0", "255,0,0");
	RUN("ERR_NO_PARAM_VEC via cilindro — retorno 1", 1,
		"miniRT: Cylinder: missing orientation vector parameter (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_VEC via cilindro --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,2,0", "2.0", "5.0", "255,0,0");
	RUN("ERR_OUT_RANGE_VEC via cilindro — retorno 1", 1,
		"miniRT: Cylinder: normalized vector value out of range [-1, 1] (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_NO_PARAM_COLOR via cilindro --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", "255,0");
	RUN("ERR_NO_PARAM_COLOR via cilindro — retorno 1", 1,
		"miniRT: Cylinder: missing color parameter (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);

	/* --- ERR_OUT_RANGE_COLOR via cilindro --- */
	sc = new_scene();
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", "256,0,0");
	RUN("ERR_OUT_RANGE_COLOR via cilindro — retorno 1", 1,
		"miniRT: Cylinder: color value out of range [0-255] (line 0)",
		cilinder_parser(p, sc));
	free_scene_obj(&sc);
}

/* ===================================================================== */
/*  SEÇÃO 11 — free_scene_obj                                            */
/* ===================================================================== */
static void	test_free_scene_obj(void)
{
	t_scene	*sc;
	char	**p;

	print_header("free_scene_obj");

	/* --- Libera cena com todos os objetos populados --- */
	sc = new_scene();
	p = make_params("A", "0.5", "255,255,255", NULL, NULL, NULL);
	amb_light_parser(p, sc);
	p = make_params("C", "0,0,0", "0,1,0", "90", NULL, NULL);
	cam_parser(p, sc);
	p = make_params("L", "0,5,0", "0.8", "255,255,255", NULL, NULL);
	light_parser(p, sc);
	p = make_params("sp", "0,0,0", "2.0", "255,0,0", NULL, NULL);
	sphere_parser(p, sc);
	p = make_params("pl", "0,0,0", "0,1,0", "100,200,50", NULL, NULL);
	plane_parser(p, sc);
	p = make_params("cy", "0,0,0", "0,1,0", "2.0", "5.0", "255,0,255");
	cilinder_parser(p, sc);
	free_scene_obj(&sc);
	if (sc == NULL)
	{ printf(GREEN "  [PASS]" RESET " cena completa liberada, ponteiro nulificado\n"); g_passed++; }
	else
	{ printf(RED "  [FAIL]" RESET " ponteiro não nulificado após free_scene_obj\n"); g_failed++; }

	/* --- Libera cena vazia (só amb/cam/light, sem objs) --- */
	sc = new_scene();
	p = make_params("A", "0.2", "0,0,0", NULL, NULL, NULL);
	amb_light_parser(p, sc);
	free_scene_obj(&sc);
	if (sc == NULL)
	{ printf(GREEN "  [PASS]" RESET " cena parcial liberada, ponteiro nulificado\n"); g_passed++; }
	else
	{ printf(RED "  [FAIL]" RESET " ponteiro não nulificado após free (parcial)\n"); g_failed++; }

	/* --- Dupla liberação não deve crashar (NULL guard) --- */
	sc = NULL;
	free_scene_obj(&sc);
	printf(GREEN "  [PASS]" RESET " free_scene_obj(NULL) não crashou\n");
	g_passed++;
}

/* ===================================================================== */
/*  SEÇÃO 12 — read_file (integração com arquivos .rt em scenes/)        */
/* ===================================================================== */

/*
** Resolve o caminho de um arquivo dentro da pasta "scenes", funcionando
** tanto quando o binário é executado a partir de test/parser (rodando
** "./test_parser" ali dentro) quanto a partir da raiz do projeto
** (rodando algo como "test/parser/test_parser").
**
** Tenta, nesta ordem:
**   1) scenes/<nome>                      (cwd == test/parser)
**   2) test/parser/scenes/<nome>          (cwd == raiz do projeto)
**   3) ./scenes/<nome>                    (fallback explícito)
**
** Retorna um buffer estático (não thread-safe, suficiente para os testes).
*/
static const char	*scene_path(const char *name)
{
	static char	buf[512];
	const char	*candidates_fmt[3];
	size_t		i;

	candidates_fmt[0] = "scenes/%s";
	candidates_fmt[1] = "test/parser/scenes/%s";
	candidates_fmt[2] = "./scenes/%s";
	i = 0;
	while (i < 3)
	{
		snprintf(buf, sizeof(buf), candidates_fmt[i], name);
		if (access(buf, F_OK) == 0)
			return (buf);
		i++;
	}
	/* nenhum candidato encontrado: devolve o primeiro para a mensagem
	** de erro do teste apontar um caminho plausível */
	snprintf(buf, sizeof(buf), candidates_fmt[0], name);
	return (buf);
}

/*
** Roda read_file() sobre um arquivo de scenes/ e verifica se o
** resultado (NULL ou não-NULL) bate com o esperado.
*/
static void	check_scene_file(const char *label, const char *filename,
								int expect_success)
{
	t_scene		*sc;
	const char	*path;

	path = scene_path(filename);
	sc = read_file(path);
	if ((sc != NULL) == (expect_success != 0))
	{
		printf(GREEN "  [PASS]" RESET " %s (%s)\n", label, filename);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %s (%s) → esperado %s, obteve %s\n",
			label, filename,
			expect_success ? "sucesso" : "NULL",
			sc != NULL ? "sucesso" : "NULL");
		g_failed++;
	}
	free_scene_obj(&sc);
}

static void	test_read_file(void)
{
	t_scene	*sc;

	print_header("read_file — cenas de test/parser/scenes");

	/* --- Casos válidos --- */
	check_scene_file("cena mínima válida",
		"valid_minimal.rt", 1);
	check_scene_file("cena com múltiplos objetos válida",
		"valid_multiple_objects.rt", 1);
	check_scene_file("linhas em branco ignoradas corretamente",
		"valid_blank_lines.rt", 1);
	check_scene_file("múltiplos espaços entre tokens ignorados",
		"valid_multiple_spaces.rt", 1);

	/* --- Objetos obrigatórios ausentes --- */
	check_scene_file("cena sem ambient retorna NULL",
		"err_no_ambient.rt", 0);
	check_scene_file("cena sem câmera retorna NULL",
		"err_no_camera.rt", 0);
	check_scene_file("cena sem light retorna NULL",
		"err_no_light.rt", 0);

	/* --- Objetos duplicados --- */
	check_scene_file("ambient duplicado retorna NULL",
		"err_dup_ambient.rt", 0);
	check_scene_file("light duplicada retorna NULL",
		"err_dup_light.rt", 0);

	/* --- Erros de valores/formatação --- */
	check_scene_file("ratio de ambient alto demais retorna NULL",
		"err_amb_rate_high.rt", 0);
	check_scene_file("ratio de ambient baixo demais retorna NULL",
		"err_amb_rate_low.rt", 0);
	check_scene_file("componente de cor alto demais retorna NULL",
		"err_color_high.rt", 0);
	check_scene_file("componente de cor baixo demais retorna NULL",
		"err_color_low.rt", 0);
	check_scene_file("fov acima do limite retorna NULL",
		"err_fov_high.rt", 0);
	check_scene_file("letras misturadas em número retorna NULL",
		"err_letters_in_number.rt", 0);
	check_scene_file("token obrigatório faltando retorna NULL",
		"err_missing_token.rt", 0);
	check_scene_file("orientação fora do intervalo retorna NULL",
		"err_orient_out_of_range.rt", 0);
	check_scene_file("diâmetro de esfera zero retorna NULL",
		"err_sphere_diam_zero.rt", 0);
	check_scene_file("tipo de objeto desconhecido retorna NULL",
		"err_unknown_type.rt", 0);

	/* --- Extensão inválida: deve retornar NULL (gerado à parte, pois não
	**     faz sentido manter um "*.txt" dentro da pasta scenes/) --- */
	{
		int	fd;

		fd = open("/tmp/invalid.txt",
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
		{
			write(fd, "A 0.5 255,255,255\nC 0,0,0 0,1,0 90\n"
				"L 0,5,0 0.8 255,255,255\n", 62);
			close(fd);
		}
		sc = read_file("/tmp/invalid.txt");
		if (sc == NULL)
		{ printf(GREEN "  [PASS]" RESET " extensão .txt rejeitada (retornou NULL)\n"); g_passed++; }
		else
		{ printf(RED "  [FAIL]" RESET " extensão .txt incorretamente aceita\n"); g_failed++; free_scene_obj(&sc); }
	}

	/* --- Arquivo inexistente --- */
	sc = read_file(scene_path("nao_existe.rt"));
	if (sc == NULL)
	{ printf(GREEN "  [PASS]" RESET " arquivo inexistente retornou NULL\n"); g_passed++; }
	else
	{ printf(RED "  [FAIL]" RESET " arquivo inexistente não retornou NULL\n"); g_failed++; free_scene_obj(&sc); }
}

/* ===================================================================== */
/*  MAIN                                                                  */
/* ===================================================================== */
int	main(void)
{
	printf(BOLD "\n╔══════════════════════════════════════════════╗\n");
	printf("║   SUITE DE TESTES — PARSERS DO MINIRT       ║\n");
	printf("╚══════════════════════════════════════════════╝" RESET "\n");

	test_print_error_all_messages();
	test_fill_color();
	test_fill_coordinate();
	test_fill_normalized();
	test_amb_light_parser();
	test_cam_parser();
	test_light_parser();
	test_sphere_parser();
	test_plane_parser();
	test_cilinder_parser();
	test_free_scene_obj();
	test_read_file();

	printf("\n" BOLD
		"══════════════════════════════════════\n"
		"  RESULTADO FINAL\n"
		"══════════════════════════════════════" RESET "\n");
	printf(GREEN "  Passou: %d\n" RESET, g_passed);
	if (g_failed > 0)
		printf(RED "  Falhou: %d\n" RESET, g_failed);
	else
		printf(GREEN "  Falhou: %d\n" RESET, g_failed);
	printf(BOLD "  Total : %d\n" RESET, g_passed + g_failed);

	return (g_failed > 0 ? 1 : 0);
}
