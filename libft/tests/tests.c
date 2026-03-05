/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:14:50 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/05 16:33:50 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

/* ========== Infraestrutura de testes ========== */

static int tests_run    = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define EPSILON 1e-9

static void run_test(const char *label, const char *input,
                     double expected, double epsilon)
{
    tests_run++;
    double result = ft_atod((char *)input);
    int ok;

    if (isnan(expected))
        ok = isnan(result);
    else if (isinf(expected))
        ok = isinf(result) && ((result > 0) == (expected > 0));
    else
        ok = fabs(result - expected) <= epsilon;

    if (ok)
    {
        tests_passed++;
        printf("  [PASS] %-45s  input: \"%-20s\"  expected: %g\n",
               label, input, expected);
    }
    else
    {
        tests_failed++;
        printf("  [FAIL] %-45s  input: \"%-20s\"  expected: %g  got: %g\n",
               label, input, expected, result);
    }
}

static void section(const char *title)
{
    printf("\n══════════════════════════════════════════════\n");
    printf("  %s\n", title);
    printf("══════════════════════════════════════════════\n");
}

/* ========== Grupos de testes ========== */

static void test_zeros(void)
{
    section("Zeros");
    run_test("zero simples",          "0",        0.0,       EPSILON);
    run_test("zero com ponto",        "0.0",      0.0,       EPSILON);
    run_test("zero negativo",         "-0.0",     0.0,       EPSILON);
    run_test("zero positivo",         "+0.0",     0.0,       EPSILON);
    run_test("ponto sem parte inteira","0.0",      0.0,       EPSILON);
}

static void test_integers(void)
{
    section("Inteiros representados como double");
    run_test("um",                    "1",        1.0,       EPSILON);
    run_test("menos um",              "-1",      -1.0,       EPSILON);
    run_test("mais um",               "+1",       1.0,       EPSILON);
    run_test("número grande",         "123456789",123456789.0, 1.0);
    run_test("número negativo grande","-987654321",-987654321.0, 1.0);
}

static void test_basic_floats(void)
{
    section("Ponto flutuante básico");
    run_test("1.5",                   "1.5",      1.5,       EPSILON);
    run_test("-1.5",                  "-1.5",    -1.5,       EPSILON);
    run_test("+1.5",                  "+1.5",     1.5,       EPSILON);
    run_test("3.14",                  "3.14",     3.14,      1e-9);
    run_test("-3.14",                 "-3.14",   -3.14,      1e-9);
    run_test("2.718281828",           "2.718281828", 2.718281828, 1e-9);
    run_test("0.1",                   "0.1",      0.1,       1e-9);
    run_test("0.001",                 "0.001",    0.001,     1e-12);
    run_test("123.456",               "123.456",  123.456,   1e-9);
    run_test("-123.456",              "-123.456",-123.456,   1e-9);
}

static void test_leading_trailing(void)
{
    section("Espaços e zeros extras");
    run_test("espaços à esquerda",    "   3.14",  3.14,      1e-9);
    run_test("tab à esquerda",        "\t3.14",   3.14,      1e-9);
    run_test("zeros à esquerda",      "007.5",    7.5,       EPSILON);
    run_test("zeros após ponto",      "3.00500",  3.005,     1e-9);
    run_test("só zeros após ponto",   "5.000",    5.0,       EPSILON);
}

static void test_only_decimal(void)
{
    section("Somente parte decimal (sem dígito antes do ponto)");
    run_test(".5",                    ".5",       0.5,       EPSILON);
    run_test(".001",                  ".001",     0.001,     1e-12);
    run_test("-.75",                  "-.75",    -0.75,      EPSILON);
    run_test("+.25",                  "+.25",     0.25,      EPSILON);
}

static void test_no_decimal(void)
{
    section("Ponto sem dígitos decimais");
    run_test("\"1.\" deve valer 1.0", "1.",       1.0,       EPSILON);
    run_test("\"-2.\" deve valer -2.0","-2.",     -2.0,      EPSILON);
}

static void test_precision(void)
{
    section("Alta precisão");
    run_test("pi com 15 casas",  "3.141592653589793", 3.141592653589793, 1e-12);
    run_test("e com 15 casas",   "2.718281828459045", 2.718281828459045, 1e-12);
    run_test("muito pequeno",    "0.000000001",        1e-9,              1e-18);
    run_test("negativo pequeno", "-0.000000001",      -1e-9,              1e-18);
}

static void test_large_values(void)
{
    section("Valores grandes");
    run_test("1e15",   "1000000000000000.0", 1e15, 1.0);
    run_test("-1e15",  "-1000000000000000.0",-1e15, 1.0);
    run_test("9.9e10", "99000000000.0",      9.9e10, 1.0);
}

static void test_signs(void)
{
    section("Sinais");
    run_test("positivo explícito +42.0", "+42.0",  42.0, EPSILON);
    run_test("negativo explícito -42.0", "-42.0", -42.0, EPSILON);
    run_test("sem sinal 42.0",           "42.0",   42.0, EPSILON);
}

static void test_rounding(void)
{
    section("Arredondamento / acúmulo de decimais");
    run_test("1/3 aprox",  "0.333333333333333", 1.0/3.0, 1e-12);
    run_test("2/3 aprox",  "0.666666666666667", 2.0/3.0, 1e-11);
    run_test("1/7 aprox",  "0.142857142857143", 1.0/7.0, 1e-12);
}

/* ========== main ========== */

int main(void)
{
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║        Testes para ft_atod                   ║\n");
    printf("╚══════════════════════════════════════════════╝\n");

    test_zeros();
    test_integers();
    test_basic_floats();
    test_leading_trailing();
    test_only_decimal();
    test_no_decimal();
    test_precision();
    test_large_values();
    test_signs();
    test_rounding();

    printf("\n══════════════════════════════════════════════\n");
    printf("  RESULTADO FINAL\n");
    printf("══════════════════════════════════════════════\n");
    printf("  Total:    %d\n", tests_run);
    printf("  Passou:   %d\n", tests_passed);
    printf("  Falhou:   %d\n", tests_failed);
    printf("  Taxa:     %.1f%%\n",
           tests_run ? 100.0 * tests_passed / tests_run : 0.0);
    printf("══════════════════════════════════════════════\n\n");

    return (tests_failed > 0 ? 1 : 0);
}
