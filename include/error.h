/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:41 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/03 14:46:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERROR "Malloc failed"
# define WALL_ERROR "There is a hole in the walls"
# define NB_ERROR "There must be one key value couple by element"
# define KEY_ERROR "Element key is invalid: \
It must be a one to two char long alphabetical string"
# define UNIQUE_KEY_ERROR "Element key is invalid: each key must be unique"
# define EL_ERROR "Element value is invalid: \
It must be either a path to <texture.xpm> or a <R,G,B> color"
# define COLOR_ERROR "Color's must be compose by three integer, \
there value must be between 0 and 255"
# define TEXTURE_ERROR "Texture couldn't be loaded"
# define FILE_ERROR "The <file.cub> is invalid"
# define MAN_TEXTURE_ERROR "The map doesn't contain all required textures: \
NO, SO, WE and EA"
# define MAN_COLOR_ERROR "The map doesn't contain all required colors: F and C"
# define OPEN_ERROR "Cannot open file"
# define SUFFIX_ERROR "Invalid suffix, use a <map.cub>"
# define CHAR_ERROR "Invalid char found in the map"
# define NO_PLAYER "No starting position was found"
# define MULTIPLE_PLAYER "Multiple starting position found"
# define MAP_TOO_BIG "The map is too big, a 300x300 is the maximum"
# define USAGE_ERROR "Usage: ./cub3d <file.cub>"
# define WINDOW_ERROR "Cannot open window"

#endif
