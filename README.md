# minishell

42 の `minishell` 課題として実装した、bash 風の小さなシェルです。
入力を読み取り、構文解析、展開、実行までを C で行います。

実装本体は [`microshell/`](./microshell) 配下にあります。

## できること

- コマンド実行
  - `PATH` から外部コマンドを探索して `execve()` で実行
  - 相対パス、絶対パス指定のコマンド実行
- パイプ
  - `cmd1 | cmd2 | cmd3`
- リダイレクト
  - 入力: `<`
  - 出力上書き: `>`
  - 出力追記: `>>`
  - heredoc: `<<`
- 環境変数展開
  - `$HOME`
  - `$?`
  - quote の扱いに応じた展開と word splitting
- builtin
  - `cd`
  - `echo`
  - `env`
  - `exit`
  - `export`
  - `pwd`
  - `unset`
- signal
  - 通常入力、heredoc、子プロセスで signal handler を切り替え

## ビルド

macOS では readline が必要です。

```sh
brew install readline
```

ビルドは実装本体のディレクトリで行います。

```sh
cd microshell
make
```

実行:

```sh
./minishell
```

削除:

```sh
make clean
make fclean
make re
```

## 使い方の例

```sh
mini('u') $ echo hello
hello

mini('u') $ export NAME=minishell
mini('u') $ echo "$NAME"
minishell

mini('u') $ cat infile | grep hello > outfile
mini('u') $ echo $?
0
```

直前の終了ステータスが `0` のときは緑、非 `0` のときは赤のプロンプトになります。

## 実行フロー

`src/main.c` の REPL は、おおまかに次の順で動きます。

1. `readline()` で入力を読む
2. parser 前の簡単な構文チェックをする
3. 入力文字列を token に分ける
4. pipe ごとの `t_command_lst` に変換する
5. parser 後の構文チェックをする
6. 環境変数、`$?`、quote を展開する
7. builtin または外部コマンドを実行する
8. 1 回の入力で確保したメモリを解放する

## ディレクトリ構成

```txt
microshell/
├── Makefile
├── inc/
│   ├── builtin.h
│   ├── env_lst.h
│   ├── exec.h
│   ├── expander.h
│   ├── parser.h
│   ├── signal_handler.h
│   ├── syntax.h
│   └── utils.h
└── src/
    ├── builtin/   builtin コマンド
    ├── env/       環境変数リスト
    ├── exec/      pipe、redirect、execve
    ├── expander/  環境変数展開、quote 除去、word splitting
    ├── libft/     libft
    ├── parser/    token 化と command list 生成
    ├── signal/    signal handler
    ├── syntax/    構文チェック
    └── main.c     REPL の入口
```

## 主なデータ構造

### `t_command_lst`

pipe で区切られたコマンドを線形リストで持ちます。
1 node が 1 つの pipe segment です。

```c
typedef struct s_command_lst
{
	char					**command_line;
	int						*is_expanded;
	struct s_command_lst	*next;
	pid_t					pid;
}	t_command_lst;
```

例:

```sh
cat file.txt | grep hello > out
```

内部では概念的に次のように扱います。

```txt
["cat", "file.txt"]
    |
["grep", "hello", ">", "out"]
```

### `t_env`

環境変数は `key` / `value` の線形リストで管理します。
外部コマンドを実行するときに `char **` に戻して `execve()` に渡します。

### `t_mobile`

シェル全体で持ち回る状態です。

```c
typedef struct s_mobile
{
	int		status;
	char	*cwd;
}	t_mobile;
```

`status` は `$?` の展開や prompt 表示に使います。

## 実装メモ

- `exit` は pipe なしの単独実行時だけ親プロセス側で処理します。
- `cd`, `export`, `unset` のように shell 本体の状態を変える builtin は、pipe なしでは親プロセスで実行します。
- redirect は command list 内の `<`, `>`, `>>`, `<<` を見て `dup2()` で標準入出力を差し替えます。
- heredoc の delimiter 自体は展開せず、本文では `$` 展開を行います。
- quote 済み token か環境変数展開された token かを `is_expanded` で追跡し、redirect 記号との区別や word splitting に使います。

## テスト

手動確認:

```sh
cd microshell
make
./minishell
```

tester を使う場合:

```sh
cd microshell/minishell_tester
./tester
./tester builtins
./tester pipes
./tester redirects
./tester syntax
```

## 対象外

この実装は 42 minishell の範囲に合わせています。
そのため、bash のすべての機能を再現しているわけではありません。

- `&&`, `||`
- sub shell
- wildcard 展開
- job control
- command substitution
