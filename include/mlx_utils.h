/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:04 by aevstign          #+#    #+#             */
/*   Updated: 2025/04/29 15:43:50 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS
# define MLX_UTILS

// Detect the operating system
# ifdef __APPLE__
// macOS Keymaps
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_FORWARD 40
#  define KEY_BACKWARD 37
# elif defined(__linux__)
// Linux Keymaps
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_FORWARD 65365 // Example, adjust as needed
#  define KEY_BACKWARD 65366 // Example, adjust as needed
# else
#  error "Unsupported operating system"
# endif

#endif