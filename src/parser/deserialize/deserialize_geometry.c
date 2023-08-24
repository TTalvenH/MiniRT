/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_geometry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:29 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/24 12:41:39 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/std.h>
#include <parser/parser.h>
#include <renderer/color.h>

t_err	deserialize_sphere(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !ft_is_float(tokens[2])
		|| !string_to_float3(tokens[3], &material.color)
		|| !color_valid(&material.color))
		return (RT_FAILURE);
	material.color = srgb_to_linear(material.color);
	geometry.data.sphere.radius = ft_atof(tokens[2]) / 2;
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);

	return (RT_SUCCESS);
}

t_err	deserialize_plane(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.plane.normal)
		|| !string_to_float3(tokens[3], &material.color)
		|| !color_valid(&material.color))
		return (RT_FAILURE);
	ft_float3_normalize(geometry.data.plane.normal);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !normal_valid(&geometry.data.plane.normal)
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	deserialize_cylinder(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 6
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.cylinder.normal)
		|| !ft_is_float(tokens[3])
		|| !ft_is_float(tokens[4])
		|| !string_to_float3(tokens[5], &material.color)
		|| !color_valid(&material.color))
		return (RT_FAILURE);
	ft_float3_normalize(geometry.data.cylinder.normal);
	geometry.data.cylinder.radius = 2 / ft_atof(tokens[3]);
	geometry.data.cylinder.height = ft_atof(tokens[4]);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !normal_valid(&geometry.data.cylinder.normal)
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
