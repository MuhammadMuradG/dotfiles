# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
setopt beep
bindkey -v
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/MuhammadMouradFbsd/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall


# -----------------------------------------------------------------------------
# Info
# -----------------------------------------------------------------------------
# There are five startup files that zsh will read commands from:
# $ZDOTDIR/.zshenv
# $ZDOTDIR/.zprofile
# $ZDOTDIR/.zshrc
# $ZDOTDIR/.zlogin
# $ZDOTDIR/.zlogout

# If ZDOTDIR is not set, then the value of HOME is used; this is the usual case.

# `.zshenv' is sourced on all invocations of the shell, unless the -f option is
# set. It should contain commands to set the command search path, plus other
# important environment variables. `.zshenv' should not contain commands that
# produce output or assume the shell is attached to a tty.

# `.zshrc' is sourced in interactive shells. It should contain commands to set
# up aliases, functions, options, key bindings, etc.

# `.zlogin' is sourced in login shells. It should contain commands that should
# be executed only in login shells. `.zlogout' is sourced when login shells exit.
# `.zprofile' is similar to `.zlogin', except that it is sourced before `.zshrc'.
# `.zprofile' is meant as an alternative to `.zlogin' for ksh fans; the two are
# not intended to be used together, although this could certainly be done if
# desired. `.zlogin' is not the place for alias definitions, options, environment
# variable settings, etc.; as a general rule, it should not change the shell
# environment at all. Rather, it should be used to set the terminal type and
# run a series of external commands (fortune, msgs, etc).


# -----------------------------------------------------------------------------
# Customs Configuration
# -----------------------------------------------------------------------------
# Set system locale
export LANG=en_US.UTF-8

# Set additional options
setopt INC_APPEND_HISTORY   # Commands are added to the history immediately
setopt HIST_IGNORE_ALL_DUPS # Not writing duplicates to the history
setopt prompt_subst         # Reevaluate the prompt each displaying time

# Bind keys
bindkey "^[[3~" delete-char
bindkey "^[[H"  beginning-of-line
bindkey "^[[4~" end-of-line

# Highlight selection
# Colorize completions using default `ls` colors.
zstyle ':completion:*' list-colors ''

# Enable keyboard navigation of completions in menu
# (not just tab/shift-tab but cursor keys as well):
zstyle ':completion:*' menu select

# persistent reshahing i.e puts new executables in the $path
# if no command is set typing in a line will cd by default
zstyle ':completion:*' rehash true

# Allow completion of ..<Tab> to ../ and beyond.
zstyle -e ':completion:*' special-dirs '[[ $PREFIX = (../)#(..) ]] && reply=(..)'

# Categorize completion suggestions with headings:
zstyle ':completion:*' group-name ''
# Style the group names
zstyle ':completion:*' format %F{yellow}%B%U%{$__DOTS[ITALIC_ON]%}%d%{$__DOTS[ITALIC_OFF]%}%b%u%f

# My aliases. '-g': for global, allow using anywhere in the commands.
alias -g full-upgrade='sudo freebsd-update upgrade; sudo freebsd-update fetch; sudo freebsd-update install; sudo pkg update; sudo pkg upgrade -y'

# Load my theme
source ~/.zsh-theme


# -----------------------------------------------------------------------------
# Zplug plugins
# -----------------------------------------------------------------------------
source ~/.zplug/init.zsh

zplug "zsh-users/zsh-autosuggestions"
zplug "zpm-zsh/colorize"
zplug "plugins/git", from:oh-my-zsh

# Set the priority when loading
# e.g., zsh-syntax-highlighting must be loaded
# after executing compinit command and sourcing other plugins
# (If the defer tag is given 2 or above, run after compinit command)
zplug "zsh-users/zsh-syntax-highlighting", defer:2

# Install plugins if there are plugins that have not been installed
if ! zplug check --verbose; then
    printf "Install? [y/N]: "
    if read -q;then
        echo; zplug install
    fi
fi

# Then, source plugins and add commands to $PATH
zplug load
