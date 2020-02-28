/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3f_to_vec4f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenard <lbenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:27:59 by lbenard           #+#    #+#             */
/*   Updated: 2019/02/20 19:21:35 by lbenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths/vec3f.h"

t_vec4f	vec3f_to_vec4f(t_vec3f src)
{
	return (ft_vec4f(src.x, src.y, src.z, 1.0f));
}