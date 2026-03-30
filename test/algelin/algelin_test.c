#include "minirt.h"

/* ==================== HELPERS ==================== */

#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define EPSILON 1e-9

static int	g_passed = 0;
static int	g_failed = 0;

static void	print_header(const char *title)
{
	printf("\n" BOLD CYAN "══════════════════════════════════════\n");
	printf("  %s\n", title);
	printf("══════════════════════════════════════" RESET "\n");
}

static void	check_double(const char *test, double got, double expected)
{
	if (fabs(got - expected) < EPSILON)
	{
		printf(GREEN "  [PASS]" RESET " %s → %.6f\n", test, got);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %s → got %.6f, esperado %.6f\n",
			test, got, expected);
		g_failed++;
	}
}

static void	check_point(const char *test, t_point got, t_point ex)
{
	if (fabs(got.x - ex.x) < EPSILON
		&& fabs(got.y - ex.y) < EPSILON
		&& fabs(got.z - ex.z) < EPSILON)
	{
		printf(GREEN "  [PASS]" RESET " %s → (%.4f, %.4f, %.4f)\n",
			test, got.x, got.y, got.z);
		g_passed++;
	}
	else
	{
		printf(RED "  [FAIL]" RESET " %s\n", test);
		printf("         got      → (%.4f, %.4f, %.4f)\n",
			got.x, got.y, got.z);
		printf("         esperado → (%.4f, %.4f, %.4f)\n",
			ex.x, ex.y, ex.z);
		g_failed++;
	}
}

/* ==================== TESTES ==================== */

/* --- zero_point --- */
static void	test_zero_point(void)
{
	print_header("zero_point");

	t_point	p = fill_point(3.0, -5.0, 7.0);
	zero_point(&p);
	check_point("zera vetor não-nulo", p, fill_point(0, 0, 0));

	t_point	z = {0, 0, 0};
	zero_point(&z);
	check_point("zera vetor já nulo", z, fill_point(0, 0, 0));
}

/* --- fill_point --- */
static void	test_fill_point(void)
{
	print_header("fill_point");

	t_point	p = fill_point(1.0, 2.0, 3.0);
	check_double("x = 1.0", p.x, 1.0);
	check_double("y = 2.0", p.y, 2.0);
	check_double("z = 3.0", p.z, 3.0);

	t_point	neg = fill_point(-4.5, 0.0, 99.9);
	check_double("x negativo = -4.5", neg.x, -4.5);
	check_double("y = 0.0", neg.y, 0.0);
	check_double("z = 99.9", neg.z, 99.9);
}

/* --- vec_add --- */
static void	test_vec_add(void)
{
	print_header("vec_add");

	t_point	a = fill_point(1, 2, 3);
	t_point	b = fill_point(4, 5, 6);
	check_point("(1,2,3)+(4,5,6)", vec_add(a, b), fill_point(5, 7, 9));

	t_point	z = fill_point(0, 0, 0);
	check_point("a + zero = a", vec_add(a, z), a);

	t_point	neg = fill_point(-1, -2, -3);
	check_point("a + (-a) = zero", vec_add(a, neg), fill_point(0, 0, 0));

	t_point	fr = fill_point(0.5, 1.5, -2.5);
	check_point("floats (0.5,1.5,-2.5)+(-0.5,-1.5,2.5)", vec_add(fr,
		fill_point(-0.5, -1.5, 2.5)), fill_point(0, 0, 0));
}

/* --- vec_sub --- */
static void	test_vec_sub(void)
{
	print_header("vec_sub");

	t_point	a = fill_point(5, 7, 9);
	t_point	b = fill_point(1, 2, 3);
	check_point("(5,7,9)-(1,2,3)", vec_sub(a, b), fill_point(4, 5, 6));

	check_point("a - a = zero", vec_sub(a, a), fill_point(0, 0, 0));

	check_point("zero - a = -a", vec_sub(fill_point(0, 0, 0), a),
		fill_point(-5, -7, -9));
}

/* --- vec_scale --- */
static void	test_vec_scale(void)
{
	print_header("vec_scale");

	t_point	a = fill_point(1, 2, 3);
	check_point("escala por 2", vec_scale(a, 2.0), fill_point(2, 4, 6));
	check_point("escala por 0", vec_scale(a, 0.0), fill_point(0, 0, 0));
	check_point("escala por -1", vec_scale(a, -1.0), fill_point(-1, -2, -3));
	check_point("escala por 0.5", vec_scale(a, 0.5), fill_point(0.5, 1.0, 1.5));
	check_point("escala por 1", vec_scale(a, 1.0), a);
}

/* --- vec_dot --- */
static void	test_vec_dot(void)
{
	print_header("vec_dot");

	t_point	a = fill_point(1, 2, 3);
	t_point	b = fill_point(4, 5, 6);
	check_double("(1,2,3)·(4,5,6) = 32", vec_dot(a, b), 32.0);

	t_point	x = fill_point(1, 0, 0);
	t_point	y = fill_point(0, 1, 0);
	check_double("x·y = 0 (perpendiculares)", vec_dot(x, y), 0.0);

	check_double("a·a = |a|²", vec_dot(a, a), 14.0);

	t_point	neg = fill_point(-1, 0, 0);
	check_double("x·(-x) = -1 (opostos)", vec_dot(x, neg), -1.0);
}

/* --- vec_cross --- */
static void	test_vec_cross(void)
{
	print_header("vec_cross");

	t_point	x = fill_point(1, 0, 0);
	t_point	y = fill_point(0, 1, 0);
	t_point	z = fill_point(0, 0, 1);

	check_point("x × y = z", vec_cross(x, y), z);
	check_point("y × x = -z", vec_cross(y, x), fill_point(0, 0, -1));
	check_point("x × x = 0 (paralelos)", vec_cross(x, x), fill_point(0, 0, 0));

	t_point	a = fill_point(1, 2, 3);
	t_point	b = fill_point(4, 5, 6);
	/* (2*6-3*5, 3*4-1*6, 1*5-2*4) = (-3, 6, -3) */
	check_point("(1,2,3)×(4,5,6)", vec_cross(a, b), fill_point(-3, 6, -3));

	/* produto cruzado ⟂ a ambos os operandos */
	t_point	c = vec_cross(a, b);
	check_double("resultado ⟂ a", vec_dot(c, a), 0.0);
	check_double("resultado ⟂ b", vec_dot(c, b), 0.0);
}

/* --- vec_magnitude --- */
static void	test_vec_magnitude(void)
{
	print_header("vec_magnitude");

	t_point	x = fill_point(1, 0, 0);
	check_double("|x| = 1", vec_magnitude(x), 1.0);

	t_point	a = fill_point(3, 4, 0);
	check_double("|(3,4,0)| = 5", vec_magnitude(a), 5.0);

	t_point	b = fill_point(1, 2, 2);
	check_double("|(1,2,2)| = 3", vec_magnitude(b), 3.0);

	t_point	z = fill_point(0, 0, 0);
	check_double("|zero| = 0", vec_magnitude(z), 0.0);
}

/* --- vec_normalize --- */
static void	test_vec_normalize(void)
{
	print_header("vec_normalize");

	t_point	a = fill_point(3, 0, 0);
	check_point("normalize (3,0,0)", vec_normalize(a), fill_point(1, 0, 0));

	t_point	b = fill_point(1, 1, 1);
	double	inv = 1.0 / sqrt(3.0);
	check_point("normalize (1,1,1)", vec_normalize(b),
		fill_point(inv, inv, inv));

	/* magnitude do resultado deve ser 1 */
	t_point	c = fill_point(2, -3, 6);
	check_double("|normalize(2,-3,6)| = 1", vec_magnitude(vec_normalize(c)), 1.0);
}

/* --- create_matrix / free_matrix --- */
static void	test_create_free_matrix(void)
{
	print_header("create_matrix / free_matrix");

	t_matrix	*m;
	int			ok;

	/* 1×1 */
	m = create_matrix(1, 1);
	ok = (m != NULL && m->row == 1 && m->col == 1 && m->a != NULL);
	if (ok)
	{ printf(GREEN "  [PASS]" RESET " create_matrix(1,1) não é NULL\n"); g_passed++; }
	else
	{ printf(RED "  [FAIL]" RESET " create_matrix(1,1) retornou NULL ou inválido\n"); g_failed++; }
	if (m) free_matrix(m);

	/* 4×4 */
	m = create_matrix(4, 4);
	ok = (m != NULL && m->row == 4 && m->col == 4 && m->a != NULL);
	if (ok)
	{ printf(GREEN "  [PASS]" RESET " create_matrix(4,4) — dimensões corretas\n"); g_passed++; }
	else
	{ printf(RED "  [FAIL]" RESET " create_matrix(4,4) — dimensões incorretas\n"); g_failed++; }

	/* células inicializadas em 0 */
	if (m)
	{
		int zero_ok = 1;
		for (int i = 0; i < m->row && zero_ok; i++)
			for (int j = 0; j < m->col && zero_ok; j++)
				if (m->a[i][j] != 0.0)
					zero_ok = 0;
		if (zero_ok)
		{ printf(GREEN "  [PASS]" RESET " células inicializadas em 0\n"); g_passed++; }
		else
		{ printf(YELLOW "  [WARN]" RESET " células não inicializadas em 0\n"); }
		free_matrix(m);
	}
}

/* --- determinant (ordem 1 a 4) --- */

static t_matrix	*make_matrix(int n, double vals[])
{
	t_matrix	*m = create_matrix(n, n);
	if (!m)
		return NULL;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			m->a[i][j] = vals[i * n + j];
	return m;
}

static void	test_determinant(void)
{
	print_header("determinant");

	t_matrix	*m;
	char		label[64];

	/* 1×1: det([7]) = 7 */
	double v1[] = {7};
	m = make_matrix(1, v1);
	snprintf(label, sizeof(label), "det([7]) = 7");
	check_double(label, determinant(*m), 7.0);
	free_matrix(m);

	/* 2×2: det([[1,2],[3,4]]) = -2 */
	double v2[] = {1, 2, 3, 4};
	m = make_matrix(2, v2);
	check_double("det([[1,2],[3,4]]) = -2", determinant(*m), -2.0);
	free_matrix(m);

	/* 2×2 identidade: det = 1 */
	double vi2[] = {1, 0, 0, 1};
	m = make_matrix(2, vi2);
	check_double("det(I2) = 1", determinant(*m), 1.0);
	free_matrix(m);

	/* 3×3: det([[6,1,1],[4,-2,5],[2,8,7]]) = -306 */
	double v3[] = {6, 1, 1, 4, -2, 5, 2, 8, 7};
	m = make_matrix(3, v3);
	check_double("det 3×3 = -306", determinant(*m), -306.0);
	free_matrix(m);

	/* 3×3 identidade: det = 1 */
	double vi3[] = {1,0,0, 0,1,0, 0,0,1};
	m = make_matrix(3, vi3);
	check_double("det(I3) = 1", determinant(*m), 1.0);
	free_matrix(m);

	/* 3×3 singular: det = 0 */
	double vs3[] = {1,2,3, 4,5,6, 7,8,9};
	m = make_matrix(3, vs3);
	check_double("det singular 3×3 = 0", determinant(*m), 0.0);
	free_matrix(m);

	/* 4×4 identidade: det = 1 */
	double vi4[] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	m = make_matrix(4, vi4);
	check_double("det(I4) = 1", determinant(*m), 1.0);
	free_matrix(m);

	/* 4×4: det = 0 (linha repetida) */
	double vr4[] = {1,2,3,4, 1,2,3,4, 5,6,7,8, 9,10,11,12};
	m = make_matrix(4, vr4);
	check_double("det 4×4 linha repetida = 0", determinant(*m), 0.0);
	free_matrix(m);

	/* 4×4 geral */
	double v4[] = {1,2,3,4,  5,6,7,8,  9,10,11,12,  3,1,4,1};
	m = make_matrix(4, v4);
	check_double("det 4×4 geral = 0", determinant(*m), 0.0);
	free_matrix(m);
}

/* --- cofactor --- */
static void	test_cofactor(void)
{
	print_header("cofactor");

	t_matrix	*m;

	/* 2×2: [[1,2],[3,4]] → cofator(0,0) = 4, cofator(0,1) = -3 */
	double v2[] = {1, 2, 3, 4};
	m = make_matrix(2, v2);
	check_double("cofator(0,0) de [[1,2],[3,4]] = 4", cofactor(*m, 0, 0), 4.0);
	check_double("cofator(0,1) de [[1,2],[3,4]] = -3", cofactor(*m, 0, 1), -3.0);
	free_matrix(m);

	/* 3×3 */
	double v3[] = {6,1,1, 4,-2,5, 2,8,7};
	m = make_matrix(3, v3);
	/* cofator(0,0) = det([[-2,5],[8,7]]) = -14-40 = -54 */
	check_double("cofator(0,0) de M3×3 = -54", cofactor(*m, 0, 0), -54.0);
	/* cofator(0,1) = -det([[4,5],[2,7]]) = -(28-10) = -18 */
	check_double("cofator(0,1) de M3×3 = -18", cofactor(*m, 0, 1), -18.0);
	/* cofator(1,0) = -det([[1,1],[8,7]]) = -(7-8) = 1 */
	check_double("cofator(1,0) de M3×3 = 1", cofactor(*m, 1, 0), 1.0);
	free_matrix(m);
}

/* ==================== MAIN ==================== */

int	main(void)
{
	printf(BOLD "\n╔══════════════════════════════════════╗\n");
	printf("║    SUITE DE TESTES — ÁLGEBRA / MATRIZES    ║\n");
	printf("╚══════════════════════════════════════╝" RESET "\n");

	test_zero_point();
	test_fill_point();
	test_vec_add();
	test_vec_sub();
	test_vec_scale();
	test_vec_dot();
	test_vec_cross();
	test_vec_magnitude();
	test_vec_normalize();
	test_create_free_matrix();
	test_determinant();
	test_cofactor();

	printf("\n" BOLD "══════════════════════════════════════\n");
	printf("  RESULTADO FINAL\n");
	printf("══════════════════════════════════════" RESET "\n");
	printf(GREEN "  Passou: %d\n" RESET, g_passed);
	if (g_failed > 0)
		printf(RED "  Falhou: %d\n" RESET, g_failed);
	else
		printf(GREEN "  Falhou: %d\n" RESET, g_failed);
	printf(BOLD "  Total : %d\n" RESET, g_passed + g_failed);

	return (g_failed > 0 ? 1 : 0);
}
