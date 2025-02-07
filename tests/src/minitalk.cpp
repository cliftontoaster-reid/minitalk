/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:30:06 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 13:17:23 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"
#include "tests.hpp"

int main()
{
  CU_pSuite pSuite = NULL;
  CU_ErrorCode error;

  // Initialize the CUnit test registry
  if (CUE_SUCCESS != (error = CU_initialize_registry()))
    goto cleanup;

  // Add a suite to the registry
  pSuite = CU_add_suite("Suite_1", 0, 0);
  if (NULL == pSuite)
    goto cleanup;

  // Add the test to the suite
  if (NULL == CU_add_test(pSuite, "Test of char_to_binary", test_char_to_binary))
    goto cleanup;
  if (NULL == CU_add_test(pSuite, "Test of send_bit", test_send_bit))
    goto cleanup;

  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

cleanup:
  CU_cleanup_registry();
  return error;
}