#!/bin/bash

# 定义支持的平台列表
SUPPORTED_PLATFORMS=("linux" "j6m_acore" "mingw")

# lunch 函数
function lunch() {
    local platform="$1"
    # 检查输入的平台是否在支持列表中
    local valid=false
    for p in "${SUPPORTED_PLATFORMS[@]}"; do
        if [ "$p" = "$platform" ]; then
            valid=true
            break
        fi
    done

    if [ "$valid" = false ]; then
        echo "不支持的平台: $platform。支持的平台有: ${SUPPORTED_PLATFORMS[*]}"
        return 1
    fi

    # 根据选择的平台设置相应的环境变量
    case "$platform" in
        "linux")
            export TARGET_PRODUCT_LINUX=1
            ;;
        "j6m_acore")
            export TARGET_PRODUCT_J6M_ACORE=1
            ;;
        "mingw")
            export TARGET_PRODUCT_MINGW=1
            ;;
    esac

    echo "已选择平台: $platform"
}