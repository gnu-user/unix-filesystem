#include <stdlib.h>
#include <check.h>
#include "../src/blockio.h"

START_TEST (test_get_block)
{
  int block_num = 10;
  byte buf[128] = {0};

  fail_unless (get_block(block_num, buf) == NULL,
           "NULL should be returned on attempt to create a "
           "block that doesn't exist");
}
END_TEST

Suite *
blockio_suite (void)
{
  Suite *s = suite_create ("blockio");

  /* Limits test case */
  TCase *tc_limits = tcase_create ("Limits");
  tcase_add_test (tc_limits, test_get_block);
  suite_add_tcase (s, tc_limits);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s = blockio_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
