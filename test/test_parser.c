#include "../includes/minirt.h"

void    print_scene(t_scene *scene);

typedef struct s_test
{
    char    *name;
    char    *file;
    int     expect_null;
}   t_test;

static void run_tests(t_test *tests, int count)
{
    int     passed;
    int     failed;
    int     i;
    t_scene *result;

    passed = 0;
    failed = 0;
    i = 0;
    while (i < count)
    {
        result = read_file(tests[i].file);
        if (tests[i].expect_null && result == NULL)
        {
            printf("[PASS] %s\n", tests[i].name);
            passed++;
        }
        else if (!tests[i].expect_null && result != NULL)
        {
            printf("[PASS] %s\n", tests[i].name);
            print_scene(result);
            free_scene_obj(&result);
            passed++;
        }
        else
        {
            printf("[FAIL] %s (expected %s, got %s)\n",
                tests[i].name,
                tests[i].expect_null ? "NULL" : "valid scene",
                result == NULL ? "NULL" : "valid scene");
            if (result)
                free_scene_obj(&result);
            failed++;
        }
        i++;
    }
    printf("\n--- Results: %d passed, %d failed ---\n", passed, failed);
}

int main(void)
{
    t_test  tests[] = {
        {"valid minimal scene",         "./scenes/valid_minimal.rt",           0},
        {"valid multiple objects",      "./scenes/valid_multiple_objects.rt",  0},
        {"valid blank lines",           "./scenes/valid_blank_lines.rt",       0},
        {"valid multiple spaces",       "./scenes/valid_multiple_spaces.rt",   0},
        {"error no ambient",            "./scenes/err_no_ambient.rt",          1},
        {"error no camera",             "./scenes/err_no_camera.rt",           1},
        {"error no light",              "./scenes/err_no_light.rt",            1},
        {"error dup ambient",           "./scenes/err_dup_ambient.rt",         1},
        {"error dup camera",            "./scenes/err_dup_camera.rt",          1},
        {"error dup light",             "./scenes/err_dup_light.rt",           1},
        {"error amb rate high",         "./scenes/err_amb_rate_high.rt",       1},
        {"error amb rate low",          "./scenes/err_amb_rate_low.rt",        1},
        {"error fov high",              "./scenes/err_fov_high.rt",            1},
        {"error orient out of range",   "./scenes/err_orient_out_of_range.rt", 1},
        {"error color high",            "./scenes/err_color_high.rt",          1},
        {"error color low",             "./scenes/err_color_low.rt",           1},
        {"error sphere diam zero",      "./scenes/err_sphere_diam_zero.rt",    1},
        {"error unknown type",          "./scenes/err_unknown_type.rt",        1},
        {"error missing token",         "./scenes/err_missing_token.rt",       1},
        {"error letters in number",     "./scenes/err_letters_in_number.rt",   1},
    };
    int count = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, count);
    return (0);
}
