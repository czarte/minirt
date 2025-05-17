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
#  define KEY_ESC 65307
#  define L_KEY_A_L 97
#  define L_KEY_D_R 100
#  define L_KEY_S_B 115
#  define L_KEY_W_U 119
#  define L_KEY_X_F 120
#  define L_KEY_y_B 121
#  define C_KEY_UP 65362
#  define C_KEY_DOWN 65364
#  define C_KEY_LEFT 65361
#  define C_KEY_RIGHT 65363
#  define C_KEY_FORWARD 65451 // Example, adjust as needed
#  define C_KEY_BACKWARD 65453 // Example, adjust as needed
#  define O_KEY_D_R 108
#  define O_KEY_S_B 107
#  define O_KEY_W_U 105
#  define O_KEY_A_L 106
#  define O_KEY_X_F 109
#  define O_KEY_y_B 110
#  define A_KEY_UP 237
#  define A_KEY_DWN 233
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
#  define KEY_ESC 65307
#  define A_KEY_UP 237
#  define A_KEY_DWN 233
#  define L_KEY_A_L 97
#  define L_KEY_D_R 100
#  define L_KEY_S_B 115
#  define L_KEY_W_U 119
#  define L_KEY_X_F 120
#  define L_KEY_y_B 121
#  define C_KEY_UP 65362
#  define C_KEY_DOWN 65364
#  define C_KEY_LEFT 65361
#  define C_KEY_RIGHT 65363
#  define C_KEY_FORWARD 65451 // Example, adjust as needed
#  define C_KEY_BACKWARD 65453 // Example, adjust as needed
#  define O_KEY_D_R 108
#  define O_KEY_S_B 107
#  define O_KEY_W_U 105
#  define O_KEY_A_L 106
#  define O_KEY_X_F 109
#  define O_KEY_y_B 110
# else
#  error "Unsupported operating system"
# endif

//ambient
//9 - 237
//0 + 233

// light
//97 a
//100 d
//115 s
//119 w
//120 x
//121 y

//objects
//105 i
//106 j
//107 k
//108 l
//109 m
//110 n

//camera
//65361 left
//65362 up
//65363 right
//65364 bottom
//65351 +
//65453 -
#endif