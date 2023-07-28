#include "shell.h"

/**
 * _Shellyenv - 現在の環境を出力します
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int _Shellyenv(feed_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - 環境変数の値を取得します
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(feed_t *info, const char *name)
{
	roster_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _Shellysetenv - 新しい環境変数を初期化し、
  * または既存のものを変更する
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int _Shellysetenv(feed_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _Shellyunsetenv - 環境変数を削除する
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int _Shellyunsetenv(feed_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - 環境リンクリストにデータを入力します
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0
 */
int populate_env_list(feed_t *info)
{
	roster_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
