#!/bin/sh

mode="$1"

STEPS=30
DELAY=0.001

normal_gamma_r=1.0
normal_gamma_g=1.0
normal_gamma_b=1.0
normal_brightness=1.0

warm_gamma_r=1.0
warm_gamma_g=0.8
warm_gamma_b=0.6
warm_brightness=0.9

state_file="${XDG_RUNTIME_DIR:-/tmp}/dwm-brightness-mode"

case "$mode" in
    warm|normal)
        ;;
    *)
        echo "Usage: $0 {warm|normal}"
        exit 1
        ;;
esac

previous_mode="$(cat "$state_file" 2>/dev/null || echo normal)"

case "$previous_mode" in
    warm)
        start_r=$warm_gamma_r
        start_g=$warm_gamma_g
        start_b=$warm_gamma_b
        start_brightness=$warm_brightness
        ;;
    *)
        start_r=$normal_gamma_r
        start_g=$normal_gamma_g
        start_b=$normal_gamma_b
        start_brightness=$normal_brightness
        ;;
esac

case "$mode" in
    warm)
        end_r=$warm_gamma_r
        end_g=$warm_gamma_g
        end_b=$warm_gamma_b
        end_brightness=$warm_brightness
        ;;
    normal)
        end_r=$normal_gamma_r
        end_g=$normal_gamma_g
        end_b=$normal_gamma_b
        end_brightness=$normal_brightness
        ;;
esac

outputs="$(xrandr --query | awk '/ connected/{print $1}')"

i=0
while [ "$i" -le "$STEPS" ]; do
    gamma_r="$(awk "BEGIN {print $start_r + ($end_r - $start_r) * $i / $STEPS}")"
    gamma_g="$(awk "BEGIN {print $start_g + ($end_g - $start_g) * $i / $STEPS}")"
    gamma_b="$(awk "BEGIN {print $start_b + ($end_b - $start_b) * $i / $STEPS}")"
    brightness="$(awk "BEGIN {print $start_brightness + ($end_brightness - $start_brightness) * $i / $STEPS}")"

    echo "$outputs" | while read -r output; do
        [ -n "$output" ] && xrandr --output "$output" \
            --gamma "$gamma_r:$gamma_g:$gamma_b" \
            --brightness "$brightness"
    done

    sleep "$DELAY"
    i=$((i + 1))
done

echo "$mode" > "$state_file"
