# Custom zsh theme by Grant Buster
# useful unicode chars: ━┏┗ ┓┛  ─╭╰ ╮╯, for more https://shapecatcher.com/
#
# Some important function:
# %F{color} Setting the foreground color
# %K{color} Setting the background color
# %F (%f) Start (stop) using a different foreground colour
# %K (%k) Start (stop) using a different bacKground colour
# %B (%b) Start (stop) boldface mode
#
# %M (%m) The short form of the current hostname
# %n The current username


function set_color() {
	# custom colors for different hosts.
	# use "spectrum_ls" to see available colors.
	# default is 066
	COLOR=006
	echo "%F{$COLOR}"
}

function reset() {
	echo "%f%k%b"
}

function chyph() {
    echo "$(set_color)─$(reset)"
}

function inbracket() {
	echo "$(set_color)[$(reset)$1$(set_color)]$(reset)"
}

function inbox() {
	echo "$(set_color)┫$(reset)$1$(set_color)┣$(reset)"
}

function user_host_prompt_info() {
    echo "$(inbracket %n%F{red}@%F{075}%M)"
}

function env_prompt_info() {
	if [[ ! -z ${VIRTUAL_ENV} ]]; then
		echo "$(inbracket "%F{213}venv::`basename \"$VIRTUAL_ENV\"`")"
	fi
}

function directory() {
	echo "$(inbracket "%F{046}%(4~|.../%3~|%~)")"
}

function current_time() {
	echo "$(inbracket "%T")"
}

function last_command_status() {
	local LAST_EXIT_CODE=$?
	if [[ "$LAST_EXIT_CODE" = "0" ]]; then
		echo "%F{046}✔ $(reset)"
	else
		echo "$(inbracket "%F{196}ExitCode::$LAST_EXIT_CODE$(reset)")"
	fi
}

function fill-line() {
	local left_len=$(prompt-length $1)
	local right_len=$(prompt-length $2)
	local pad_len=$((COLUMNS - left_len - right_len - 1))
	local pad=${(pl.$pad_len..─.)}  # pad_len spaces
	echo ${1}$(set_color)${pad}$(reset)${2}
}

function prompt-length() {
	emulate -LR zsh
		local -i x y=${#1} m
		if (( y )); then
			while (( ${${(%):-$1%$y(l.1.0)}[-1]} )); do
				x=y
				(( y *= 2 ))
			done
			while (( y > x + 1 )); do
				(( m = x + (y - x) / 2 ))
				(( ${${(%):-$1%$m(l.x.y)}[-1]} = m ))
			done
		fi
	echo $x
}

function set-prompt() {
	local top_left=" $(set_color)╭$(env_prompt_info)$(chyph)$(directory)"

	if [[ ! -z ${INCOGNITO_MODE} ]]; then
		local bottom_left=" $(set_color)╰─$(inbracket "%F{red}IncognitoMode$(set_color)")->$(reset) "
		local top_right="$(git_prompt_info)$(inbracket Anonymous%F{red}@%F{075}HostMachine)$(set_color)─╮$(reset)"
	else
		local bottom_left=" $(set_color)╰─>$(reset) "
		local top_right="$(git_prompt_info)$(user_host_prompt_info)$(set_color)─╮$(reset)"
	fi

	local bottom_right='$(last_command_status)'"$(chyph)$(chyph)$(current_time)$(set_color)─╯$(reset)"

	PROMPT=$'\n'$(fill-line "$top_left" "$top_right")$'\n'$bottom_left
	RPROMPT=$bottom_right
}


autoload -Uz add-zsh-hook
add-zsh-hook precmd set-prompt


# GIT theme configurations
ZSH_THEME_GIT_PROMPT_PREFIX="$(set_color)[$(reset)git::"
ZSH_THEME_GIT_PROMPT_SUFFIX="$(set_color)]$(reset)$(chyph)"
ZSH_THEME_GIT_PROMPT_DIRTY=" %F{196}✘ $(reset)"
ZSH_THEME_GIT_PROMPT_CLEAN=" %F{046}✔ $(reset)"
