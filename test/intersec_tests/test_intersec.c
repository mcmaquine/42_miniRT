#include "../../includes/minirt.h"
#include <stdio.h>
#include <math.h>

typedef struct s_test
{
    char    *name;
    char    *scene_file;
    int     expect_hit;
    int     expect_type;
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
    win.scene_obj = scene;
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

static void run_tests(t_test *tests, int count, char *argv0)
{
    int         passed;
    int         failed;
    int         i;
    t_scene     *scene;
    t_window    win;
    t_ray       ray;
    t_hit       hit;
    int         got_hit;
    int         got_type;
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
        ray = generate_ray(&win, win.width / 2, win.height / 2);
        hit = all_intersections(&win, ray);
        got_hit = hit.t > 0;
        got_type = hit.obj ? (int)((t_scene_obj *)hit.obj)->base : -1;
        if (got_hit == tests[i].expect_hit
            && (!tests[i].expect_hit || got_type == tests[i].expect_type))
        {
            printf("[PASS] %s", tests[i].name);
            if (got_hit)
                printf(" | t=%.4f type=%s", hit.t, type_to_str(got_type));
            printf("\n");
            passed++;
        }
        else
        {
            printf("[FAIL] %s | expected hit=%d type=%s | got hit=%d type=%s t=%.4f\n",
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

int main(int argc, char **argv)
{
    t_test  tests[] = {
        {"sphere hit center",       "sphere_hit.rt",          1, SPHERE},
        {"sphere miss",             "sphere_miss.rt",         0, -1},
        {"plane hit",               "plane_hit.rt",           1, PLANE},
        {"plane miss",              "plane_miss.rt",          0, -1},
        {"cylinder hit",            "cylinder_hit.rt",        1, CYLINDER},
        {"cylinder miss",           "cylinder_miss.rt",       0, -1},
        {"multiple objects",        "multiple_objects.rt",    1, SPHERE},
        {"camera inside sphere",    "camera_inside_sphere.rt",1, SPHERE},
        {"sphere tangent",          "sphere_tangent.rt",          1, SPHERE},
        {"camera inside cylinder",  "camera_inside_cylinder.rt",  1, CYLINDER},
        {"closest of two spheres",  "closest_of_two_spheres.rt",  1, SPHERE},
    };
    (void)argc;
    int count = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, count, argv[0]);
    return (0);
}
