/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenard <lbenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:41:35 by lbenard           #+#    #+#             */
/*   Updated: 2019/02/20 18:21:32 by lbenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# ifdef __linux__
#  include <sys/types.h>
# else
#  include <stdint.h>
# endif

typedef uint8_t		t_u8;
typedef int8_t		t_i8;
typedef uint16_t	t_u16;
typedef int16_t		t_i16;
typedef uint32_t	t_u32;
typedef int32_t		t_i32;
typedef uint64_t	t_u64;
typedef int64_t		t_i64;

typedef uint8_t		t_bool;

typedef enum		e_result
{
	ERROR,
	OK
}					t_result;

#endif
