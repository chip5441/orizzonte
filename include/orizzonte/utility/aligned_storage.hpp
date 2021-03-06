// Copyright (c) 2017 Vittorio Romeo
// MIT License |  https://opensource.org/licenses/MIT
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>
#include "./movable_atomic.hpp"

namespace orizzonte::utility
{
    /// @brief Provides aligned storage for a `T` instance and utilities to
    /// construct/destroy/access the stored `T`.
    template <typename T>
    class aligned_storage_for
    {
    private:
        std::aligned_storage_t<sizeof(T), alignof(T)> _storage;

        // TODO: more portable
#ifndef DNDEBUG
        bool _engaged{false};

        // clang-format off
        void set_engaged() noexcept      { _engaged = true; }
        void set_unengaged() noexcept    { _engaged = false; }
        void assert_engaged() noexcept   { assert(_engaged); }
        void assert_unengaged() noexcept { assert(!_engaged); }
        // clang-format on
#else
        // clang-format off
        constexpr void set_engaged() noexcept      { }
        constexpr void set_unengaged() noexcept    { }
        constexpr void assert_engaged() noexcept   { }
        constexpr void assert_unengaged() noexcept { }
        // clang-format on
#endif

    public:
        /// @brief Constructs a new instance of `T` in the storage using
        /// perfect-forwarding and placement-new. The behavior is undefined if a
        /// `T` instance was already constructed beforehand and not destroyed.
        template <typename... TFwds>
        void construct(TFwds&&... xs)
        {
            assert_unengaged();
            new(&_storage) T(FWD(xs)...);
            set_engaged();
        }

        /// @brief Returns a reference to the stored `T`. The behavior is
        /// undefined if a `T` instance wasn't successfully constructed
        /// beforehand.
        T& access() noexcept
        {
            assert_engaged();
            return reinterpret_cast<T&>(_storage);
        }

        /// @copydoc access
        const T& access() const noexcept
        {
            assert_engaged();
            return reinterpret_cast<T&>(_storage);
        }

        /// @brief Invokes the destructor of the currently stored `T`. The
        /// behavior is undefined if a `T` instance wasn't successfully
        /// constructed beforehand.
        void destroy()
        {
            assert_engaged();
            access().~T();
            set_unengaged();
        }

        /// @brief Pointer-like interface. Equivalent to invoking `access()`.
        T& operator*() noexcept
        {
            return access();
        }

        /// @copydoc operator*
        const T& operator*() const noexcept
        {
            return access();
        }

        /// @copydoc operator*
        T* operator->() noexcept
        {
            return &access();
        }

        /// @copydoc operator*
        const T* operator->() const noexcept
        {
            return &access();
        }
    };
}
