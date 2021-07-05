#pragma once

#define COBALT_NO_COPY(cls)                                                    \
    cls(const cls&) = delete;                                                  \
    cls& operator=(const cls&) = delete;

#define COBALT_NO_MOVE(cls)                                                    \
    cls(cls&&) noexcept = delete;                                              \
    cls& operator=(cls&&) noexcept = delete;

#define COBALT_NO_COPY_MOVE(cls)                                               \
    COBALT_NO_COPY(cls)                                                        \
    COBALT_NO_MOVE(cls)

#define COBALT_NO_DISCARD [[nodiscard]]
