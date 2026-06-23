#include "../../includes/minirt.h"
#include <stdio.h>
#include <math.h>

typedef struct s_test
{
    char    *name;
    char    *scene_file;
    int     expect_hit;
    int     check_color;
    REAL    expected_red;
    REAL    expected_green;
    REAL    expected_blue;
    REAL    tolerance;
    int     check_normal;
    REAL    expected_nx;
    REAL    expected_ny;
    REAL    expected_nz;
}   t_test;

static char *build_path(char *argv0, char *scene_file)
{
    char    *last_slash;
    char    *dir;
    char    *path;
    int     dir_len;
    int     scenes_len;
    int     file_len;

    last_slash = ft_strrchr(argv0, '/');
    if (!last_slash)
        dir = ft_strdup("./");
    else
    {
        dir_len = last_slash - argv0 + 2;
        dir = ft_calloc(dir_len, sizeof(char));
        ft_strlcpy(dir, argv0, dir_len);
        dir[dir_len - 2] = '/';
        dir[dir_len - 1] = '\0';
    }
    scenes_len = ft_strlen("scenes/");
    file_len = ft_strlen(scene_file);
    dir_len = ft_strlen(dir);
    path = ft_calloc(dir_len + scenes_len + file_len + 1, sizeof(char));
    ft_strlcpy(path, dir, dir_len + 1);
    ft_strlcat(path, "scenes/", dir_len + scenes_len + 1);
    ft_strlcat(path, scene_file, dir_len + scenes_len + file_len + 1);
    free(dir);
    return (path);
}

static t_window setup_window(t_scene *scene)
{
    t_window    win;

    ft_memset(&win, 0, sizeof(t_window));
    calc_components(scene);
    win.scene_obj = *scene;
    win.width = 800;
    win.height = 600;
    win.mlx = NULL;
    win.win = NULL;
    return (win);
}

static int color_approx(REAL got, REAL expected, REAL tol)
{
    return (fabs(got - expected) <= tol);
}

static int normal_approx(t_point n, REAL nx, REAL ny, REAL nz, REAL tol)
{
    return (fabs(n.x - nx) <= tol
        && fabs(n.y - ny) <= tol
        && fabs(n.z - nz) <= tol);
}

static void run_tests(t_test *tests, int count, char *argv0)
{
    int         passed;
    int         failed;
    int         i;
    t_scene     *scene;
    t_window    win;
    t_hit       hit;
    t_color     color;
    int         ok;
    char        *path;

    passed = 0;
    failed = 0;
    i = 0;
    while (i < count)
    {
        path = build_path(argv0, tests[i].scene_file);
        scene = read_file(path);
        free(path);
        if (!scene)
        {
            printf("[FAIL] %s — could not parse scene\n", tests[i].name);
            failed++;
            i++;
            continue ;
        }
        win = setup_window(scene);
        hit = all_intersections(&win, win.width / 2, win.height / 2);
        if (!tests[i].expect_hit)
        {
            if (hit.t < 0)
            {
                printf("[PASS] %s — no hit as expected\n", tests[i].name);
                passed++;
            }
            else
            {
                printf("[FAIL] %s — expected no hit but got t=%.4f\n",
                    tests[i].name, hit.t);
                failed++;
            }
            free_scene_obj(&scene);
            i++;
            continue ;
        }
        ok = 1;
        color = calculate_illumination(&win, hit);
        if (tests[i].check_color)
        {
            if (!color_approx(color.red, tests[i].expected_red, tests[i].tolerance)
                || !color_approx(color.green, tests[i].expected_green, tests[i].tolerance)
                || !color_approx(color.blue, tests[i].expected_blue, tests[i].tolerance))
            {
                printf("[FAIL] %s | color expected=(%.3f,%.3f,%.3f) got=(%.3f,%.3f,%.3f)\n",
                    tests[i].name,
                    tests[i].expected_red, tests[i].expected_green, tests[i].expected_blue,
                    color.red, color.green, color.blue);
                ok = 0;
            }
        }
        if (tests[i].check_normal)
        {
            if (!normal_approx(hit.normal,
                tests[i].expected_nx, tests[i].expected_ny, tests[i].expected_nz,
                tests[i].tolerance))
            {
                printf("[FAIL] %s | normal expected=(%.3f,%.3f,%.3f) got=(%.3f,%.3f,%.3f)\n",
                    tests[i].name,
                    tests[i].expected_nx, tests[i].expected_ny, tests[i].expected_nz,
                    hit.normal.x, hit.normal.y, hit.normal.z);
                ok = 0;
            }
        }
        if (ok)
        {
            printf("[PASS] %s | color=(%.3f,%.3f,%.3f) normal=(%.3f,%.3f,%.3f)\n",
                tests[i].name,
                color.red, color.green, color.blue,
                hit.normal.x, hit.normal.y, hit.normal.z);
            passed++;
        }
        else
            failed++;
        free_scene_obj(&scene);
        i++;
    }
    printf("\n--- Results: %d passed, %d failed ---\n", passed, failed);
}

int main(int argc, char **argv)
{
    t_test  tests[] = {
        {"ambient only red sphere",
            "amb_red_sphere.rt",
            1, 1, 0.2, 0.0, 0.0, 0.05, 0, 0, 0, 0},
        {"diffuse perpendicular light",
            "diff_perpendicular.rt",
            1, 1, 1.0, 1.0, 1.0, 0.05, 0, 0, 0, 0},
        {"diffuse parallel light no contribution",
            "diff_parallel.rt",
            1, 1, 0.0, 0.0, 0.0, 0.05, 0, 0, 0, 0},
        {"clamp test all channels max",
            "clamp_test.rt",
            1, 1, 1.0, 1.0, 1.0, 0.01, 0, 0, 0, 0},
        {"no hit returns background",
            "no_hit.rt",
            0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0},
        {"ambient and diffuse plane",
            "amb_diffuse_plane.rt",
            1, 0, 0, 0, 0, 0.05, 1, 0.0, 1.0, 0.0},
        {"ambient and diffuse cylinder side",
            "amb_diffuse_cylinder_side.rt",
            1, 0, 0, 0, 0, 0.05, 1, -1.0, 0.0, 0.0},
        {"ambient and diffuse cylinder cap",
            "amb_diffuse_cylinder_cap.rt",
            1, 0, 0, 0, 0, 0.05, 1, 0.0, 1.0, 0.0},
        {"light behind object ambient only",
            "light_behind_object.rt",
            1, 1, 0.2, 0.2, 0.2, 0.05, 0, 0, 0, 0},
        {"black object zero color",
            "black_object.rt",
            1, 1, 0.0, 0.0, 0.0, 0.01, 0, 0, 0, 0},
        {"zero ambient only diffuse",
            "zero_ambient.rt",
            1, 1, 0.0, 0.0, 0.0, 0.05, 0, 0, 0, 0},
        {"mixed color object",
            "mixed_color_object.rt",
            1, 1, 0.2, 0.1, 0.0, 0.05, 0, 0, 0, 0},
        {"two objects closest is red",
            "two_objects_closest.rt",
            1, 1, 0.0, 0.0, 0.0, 0.05, 0, 0, 0, 0},
    };
    (void)argc;
    int count = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, count, argv[0]);
    return (0);
}