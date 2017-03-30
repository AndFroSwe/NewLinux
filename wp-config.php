<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wpDB');

/** MySQL database username */
define('DB_USER', 'wpdbprime');

/** MySQL database password */
define('DB_PASSWORD', 'WordPressDB');

/** MySQL hostname */
define('DB_HOST', 'localhost');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8mb4');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         '?Zar :;)fVI<@cnwJ~2N>G;LN>DK[!u3w<|7|jY*#--u-!|8/;KA-MDMP/B~E{-,');
define('SECURE_AUTH_KEY',  '%pJ7urwr`!2A/oN[J*%2~.]3!)q-.t.H4Z6X~<`=m|EbtvX9*ck(pmMuD9Qnc&PR');
define('LOGGED_IN_KEY',    '-DE@:ZOAVa .tf#|o{S+o~& p`NWW1_e{M}6:xP),hq>H6z)Cnbgt:_ 2IADOlB*');
define('NONCE_KEY',        'a.*6/)=2KRAVvw$D,4)4=3bEEH%ACQvSzXZf&nhf4kN0h?,3W2FWwHGU`?ld&3EE');
define('AUTH_SALT',        '`|.3AB])QD7ohV|Fj2H,jN)L!p{}Y})@M(WKg;CNt8~I3mv*cVq%]#p[e)IigL.{');
define('SECURE_AUTH_SALT', 'jM>o.|>{;!sCBZiU)z+5i^&Th+~M`iq2Qv!~zi^a0_E}L|{=6tQZN8-{ZEkkd@(~');
define('LOGGED_IN_SALT',   '9tLR_QMiS#)URDO<:}7@rpz$SN lZ5{z!( pI}l!<}{?&j^}Oh;T/Bb,x8[24N,2');
define('NONCE_SALT',       'P1JGOB1j:Ybmsy%1:se$x+AYuoM*$<4yx0yo-NkPQF(.9v}68_S+h`,0j@IT7`h/');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
