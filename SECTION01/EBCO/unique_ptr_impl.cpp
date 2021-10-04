template <class _Dx2>
using _Unique_ptr_enable_default_t =
enable_if_t<conjunction_v<negation<is_pointer<_Dx2>>, is_default_constructible<_Dx2>>, int>;


// CLASS TEMPLATE unique_ptr SCALAR
template <class _Ty, class _Dx /* = default_delete<_Ty> */>
class unique_ptr { // non-copyable pointer to an object
public:
    using pointer = typename _Get_deleter_pointer_type<_Ty, remove_reference_t<_Dx>>::type;
    using element_type = _Ty;
    using deleter_type = _Dx;

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr() noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr(nullptr_t) noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    explicit unique_ptr(pointer _Ptr) noexcept : _Mypair(_Zero_then_variadic_args_t{}, _Ptr) {}

    template <class _Dx2 = _Dx, enable_if_t<is_constructible_v<_Dx2, const _Dx2&>, int> = 0>
    unique_ptr(pointer _Ptr, const _Dx& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _Dt, _Ptr) {}

    template <class _Dx2 = _Dx,
        enable_if_t<conjunction_v<negation<is_reference<_Dx2>>, is_constructible<_Dx2, _Dx2>>, int> = 0>
        unique_ptr(pointer _Ptr, _Dx&& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _Ptr) {}

    template <class _Dx2 = _Dx,
        enable_if_t<conjunction_v<is_reference<_Dx2>, is_constructible<_Dx2, remove_reference_t<_Dx2>>>, int> = 0>
        unique_ptr(pointer, remove_reference_t<_Dx>&&) = delete;

    //============================================================
    // move
    template <class _Dx2 = _Dx, enable_if_t<is_move_constructible_v<_Dx2>, int> = 0>
    unique_ptr(unique_ptr&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx>(_Right.get_deleter()), _Right.release()) {}

    template <class _Ty2, class _Dx2,
        enable_if_t<
        conjunction_v<negation<is_array<_Ty2>>, is_convertible<typename unique_ptr<_Ty2, _Dx2>::pointer, pointer>,
        conditional_t<is_reference_v<_Dx>, is_same<_Dx2, _Dx>, is_convertible<_Dx2, _Dx>>>,
        int> = 0>
        unique_ptr(unique_ptr<_Ty2, _Dx2>&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx2>(_Right.get_deleter()), _Right.release()) {}
    //===================================================

    template <class _Ty2, class _Dx2,
        enable_if_t<conjunction_v<negation<is_array<_Ty2>>, is_assignable<_Dx&, _Dx2>,
        is_convertible<typename unique_ptr<_Ty2, _Dx2>::pointer, pointer>>,
        int> = 0>
        unique_ptr& operator=(unique_ptr<_Ty2, _Dx2>&& _Right) noexcept {
        reset(_Right.release());
        _Mypair._Get_first() = _STD forward<_Dx2>(_Right._Mypair._Get_first());
        return *this;
    }

    template <class _Dx2 = _Dx, enable_if_t<is_move_assignable_v<_Dx2>, int> = 0>
    unique_ptr& operator=(unique_ptr&& _Right) noexcept {
        if (this != _STD addressof(_Right)) {
            reset(_Right.release());
            _Mypair._Get_first() = _STD forward<_Dx>(_Right._Mypair._Get_first());
        }
        return *this;
    }

    void swap(unique_ptr& _Right) noexcept {
        _Swap_adl(_Mypair._Myval2, _Right._Mypair._Myval2);
        _Swap_adl(_Mypair._Get_first(), _Right._Mypair._Get_first());
    }

    unique_ptr& operator=(nullptr_t) noexcept {
        reset();
        return *this;
    }

    ~unique_ptr() noexcept 
    {
        if (_Mypair._Myval2) {
            _Mypair._Get_first()(_Mypair._Myval2);
        }
    }

    _Dx& get_deleter() noexcept             { return _Mypair._Get_first(); }
    const _Dx& get_deleter() const noexcept { return _Mypair._Get_first(); }

    add_lvalue_reference_t<_Ty> operator*() const noexcept { return *_Mypair._Myval2;  }
    pointer operator->() const noexcept { return _Mypair._Myval2;  }

    pointer get() const noexcept { return _Mypair._Myval2;  }

    explicit operator bool() const noexcept {  return static_cast<bool>(_Mypair._Myval2); }

    pointer release() noexcept { return _STD exchange(_Mypair._Myval2, nullptr); }

    void reset(pointer _Ptr = nullptr) noexcept 
    {
        pointer _Old = _STD exchange(_Mypair._Myval2, _Ptr);
        if (_Old) {
            _Mypair._Get_first()(_Old);
        }
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

private:
    template <class, class>
    friend class unique_ptr;

    _Compressed_pair<_Dx, pointer> _Mypair;
};



// CLASS TEMPLATE unique_ptr ARRAY
template <class _Ty, class _Dx>
class unique_ptr<_Ty[], _Dx> { // non-copyable pointer to an array object
public:
    using pointer = typename _Get_deleter_pointer_type<_Ty, remove_reference_t<_Dx>>::type;
    using element_type = _Ty;
    using deleter_type = _Dx;

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr() noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    template <class _Uty, class _Is_nullptr = is_same<_Uty, nullptr_t>>
    using _Enable_ctor_reset =
        enable_if_t<is_same_v<_Uty, pointer> //
        || _Is_nullptr::value //
        || (is_same_v<pointer, element_type*> //
            && is_pointer_v<_Uty> //
            && is_convertible_v<remove_pointer_t<_Uty>(*)[], element_type(*)[]>)>; // TRANSITION, GH-248

    template <class _Uty, class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0, class = _Enable_ctor_reset<_Uty>>
    explicit unique_ptr(_Uty _Ptr) noexcept : _Mypair(_Zero_then_variadic_args_t{}, _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx, enable_if_t<is_constructible_v<_Dx2, const _Dx2&>, int> = 0,
        class = _Enable_ctor_reset<_Uty>>
        unique_ptr(_Uty _Ptr, const _Dx& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _Dt, _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx,
        enable_if_t<conjunction_v<negation<is_reference<_Dx2>>, is_constructible<_Dx2, _Dx2>>, int> = 0,
        class = _Enable_ctor_reset<_Uty>>
        unique_ptr(_Uty _Ptr, _Dx&& _Dt) noexcept : _Mypair(_One_then_variadic_args_t{}, _STD move(_Dt), _Ptr) {}

    template <class _Uty, class _Dx2 = _Dx,
        enable_if_t<conjunction_v<is_reference<_Dx2>, is_constructible<_Dx2, remove_reference_t<_Dx2>>>, int> = 0>
        unique_ptr(_Uty, remove_reference_t<_Dx>&&) = delete;

    template <class _Dx2 = _Dx, enable_if_t<is_move_constructible_v<_Dx2>, int> = 0>
    unique_ptr(unique_ptr&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Dx>(_Right.get_deleter()), _Right.release()) {}

    template <class _Dx2 = _Dx, enable_if_t<is_move_assignable_v<_Dx2>, int> = 0>
    unique_ptr& operator=(unique_ptr&& _Right) noexcept {
        if (this != _STD addressof(_Right)) {
            reset(_Right.release());
            _Mypair._Get_first() = _STD move(_Right._Mypair._Get_first());
        }

        return *this;
    }

    template <class _Uty, class _Ex, class _More, class _UP_pointer = typename unique_ptr<_Uty, _Ex>::pointer,
        class _UP_element_type = typename unique_ptr<_Uty, _Ex>::element_type>
        using _Enable_conversion = enable_if_t<
        conjunction_v<is_array<_Uty>, is_same<pointer, element_type*>, is_same<_UP_pointer, _UP_element_type*>,
        is_convertible<_UP_element_type(*)[], element_type(*)[]>, _More>>; // TRANSITION, GH-248

    template <class _Uty, class _Ex,
        class = _Enable_conversion<_Uty, _Ex,
        conditional_t<is_reference_v<_Dx>, is_same<_Ex, _Dx>, is_convertible<_Ex, _Dx>>>>
        unique_ptr(unique_ptr<_Uty, _Ex>&& _Right) noexcept
        : _Mypair(_One_then_variadic_args_t{}, _STD forward<_Ex>(_Right.get_deleter()), _Right.release()) {}

    template <class _Uty, class _Ex, class = _Enable_conversion<_Uty, _Ex, is_assignable<_Dx&, _Ex>>>
    unique_ptr& operator=(unique_ptr<_Uty, _Ex>&& _Right) noexcept {
        reset(_Right.release());
        _Mypair._Get_first() = _STD forward<_Ex>(_Right._Mypair._Get_first());
        return *this;
    }

    template <class _Dx2 = _Dx, _Unique_ptr_enable_default_t<_Dx2> = 0>
    constexpr unique_ptr(nullptr_t) noexcept : _Mypair(_Zero_then_variadic_args_t{}) {}

    unique_ptr& operator=(nullptr_t) noexcept {
        reset();
        return *this;
    }

    void reset(nullptr_t = nullptr) noexcept {
        reset(pointer());
    }

    void swap(unique_ptr& _Right) noexcept {
        _Swap_adl(_Mypair._Myval2, _Right._Mypair._Myval2);
        _Swap_adl(_Mypair._Get_first(), _Right._Mypair._Get_first());
    }

    ~unique_ptr() noexcept {
        if (_Mypair._Myval2) {
            _Mypair._Get_first()(_Mypair._Myval2);
        }
    }

    _NODISCARD _Dx& get_deleter() noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD const _Dx& get_deleter() const noexcept {
        return _Mypair._Get_first();
    }

    _NODISCARD _Ty& operator[](size_t _Idx) const noexcept /* strengthened */ {
        return _Mypair._Myval2[_Idx];
    }

    _NODISCARD pointer get() const noexcept {
        return _Mypair._Myval2;
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(_Mypair._Myval2);
    }

    pointer release() noexcept {
        return _STD exchange(_Mypair._Myval2, nullptr);
    }

    template <class _Uty, class = _Enable_ctor_reset<_Uty, false_type>>
    void reset(_Uty _Ptr) noexcept {
        pointer _Old = _STD exchange(_Mypair._Myval2, _Ptr);
        if (_Old) {
            _Mypair._Get_first()(_Old);
        }
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

private:
    template <class, class>
    friend class unique_ptr;

    _Compressed_pair<_Dx, pointer> _Mypair;
};