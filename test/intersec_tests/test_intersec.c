#include "../../includes/minirt.h"
#include <stdio.h>

typedef struct s_test
{
    char    *name;
    char    *file;
    int     expect_hit;
    int     expect_type;
}   t_test;

static t_window setup_window(t_scene *scene)
{
    t_window    win;

    ft_memset(&win, 0, sizeof(t_window));
    win.scene_obj = *scene;
    win.width = 800;
    win.height = 600;
    win.mlx = NULL;
    win.win = NULL;
    return (win);
}

static char *type_to_str(int type)
{
    if (type == SPHERE)
        return ("SPHERE");
    if (type == PLANE)
        return ("PLANE");
    if (type == CYLINDER)
        return ("CYLINDER");
    return ("UNKNOWN");
}

static void run_tests(t_test *tests, int count)
{
    int         passed;
    int         failed;
    int         i;
    t_scene     *scene;
    t_window    win;
    t_hit       hit;
    int         got_hit;
    int         got_type;

    passed = 0;
    failed = 0;
    i = 0;
    while (i < count)
    {
        scene = read_file(tests[i].file);
        if (!scene)
        {
            printf("[FAIL] %s — could not parse scene\n", tests[i].name);
            failed++;
            i++;
            continue ;
        }
        calc_components(scene);
        win = setup_window(scene);
        hit = all_intersections(&win, win.width / 2, win.height / 2);
        got_hit = hit.t > 0;
        got_type = hit.obj ? (int)((t_scene_obj *)hit.obj)->base : -1;
        if (got_hit == tests[i].expect_hit
            && (!tests[i].expect_hit || got_type == tests[i].expect_type))
        {
            printf("\e[32m[PASS]\e[0m %s", tests[i].name);
            if (got_hit)
                printf(" | t=%.4f type=%s", hit.t, type_to_str(got_type));
            printf("\n");
            passed++;
        }
        else
        {
            printf("\e[31m[FAIL]\e[0m %s | expected hit=%d type=%s | got hit=%d type=%s t=%.4f\n",
                tests[i].name,
                tests[i].expect_hit,
                type_to_str(tests[i].expect_type),
                got_hit,
                type_to_str(got_type),
                hit.t);
            failed++;
        }
        free_scene_obj(&scene);
        i++;
    }
    printf("\n--- Results: %d passed, %d failed ---\n", passed, failed);
}

int main(void)
{
    t_test  tests[] = {
        {"sphere hit center",       "test/intersec_tests/scenes/sphere_hit.rt",          1, SPHERE},
        {"sphere miss",             "test/intersec_tests/scenes/sphere_miss.rt",         0, -1},
        {"plane hit",               "test/intersec_tests/scenes/plane_hit.rt",           1, PLANE},
        {"plane miss",              "test/intersec_tests/scenes/plane_miss.rt",          0, -1},
        {"cylinder hit",            "test/intersec_tests/scenes/cylinder_hit.rt",        1, CYLINDER},
        {"cylinder miss",           "test/intersec_tests/scenes/cylinder_miss.rt",       0, -1},
        {"multiple objects",        "test/intersec_tests/scenes/multiple_objects.rt",    1, SPHERE},
        {"camera inside sphere",    "test/intersec_tests/scenes/camera_inside_sphere.rt",1, SPHERE},
    };
    int count = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, count);
    return (0);
}