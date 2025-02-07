/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:34:07 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:42:49 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUnit/Basic.h"
#include <sys/wait.h>

extern "C"
{
#include "sig.h"
}

void test_char_to_binary(void)
{
  int binary[8];
  char_to_binary('a', binary);
  CU_ASSERT_EQUAL(binary[0], 0);
  CU_ASSERT_EQUAL(binary[1], 1);
  CU_ASSERT_EQUAL(binary[2], 1);
  CU_ASSERT_EQUAL(binary[3], 0);
  CU_ASSERT_EQUAL(binary[4], 0);
  CU_ASSERT_EQUAL(binary[5], 0);
  CU_ASSERT_EQUAL(binary[6], 0);
  CU_ASSERT_EQUAL(binary[7], 1);
}

void test_send_bit(void)
{
  int pid = getpid();

  signal(SIGUSR1, [](int signum)
         { (void)signum; CU_PASS("Signal SIGUSR1 received"); });

  int owo = fork();

  if (owo == 0)
  {
    send_bit(pid, 1);
    exit(0);
  }
  else
  {
    waitpid(owo, NULL, 0);
  }
}
