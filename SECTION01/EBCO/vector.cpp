 vector() noexcept(is_nothrow_default_constructible_v<_Alty>) : _Mypair(_Zero_then_variadic_args_t()) {
 
     _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
 
 } 
 
 explicit vector(const _Alloc& _Al) noexcept : _Mypair(_One_then_variadic_args_t(), _Al) {
 
     _Mypair._Myval2._Alloc_proxy(_GET_PROXY_ALLOCATOR(_Alty, _Getal()));
 
 }