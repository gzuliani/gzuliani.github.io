#include <functional>

template<typename R, typename... Args>
class Delegate {
    typedef std::function<R(Args...)> Fn;
    Fn fn_;
    template<class T>
    struct FnMemCall {
        T* obj_;
        typedef R (T::*Fn)(Args...);
        Fn fn_;
        FnMemCall(T* obj, Fn fn) : obj_(obj), fn_(fn) { }
        R operator()(Args... args) const {
            return (obj_->*fn_)(args...);
        }
    };
    template<class T>
    struct ConstFnMemCall {
        const T* obj_;
        typedef R (T::*Fn)(Args...) const;
        Fn fn_;
        ConstFnMemCall(const T* obj, Fn fn) : obj_(obj), fn_(fn) { }
        R operator()(Args... args) const {
            return (obj_->*fn_)(args...);
        }
    };
public:
    Delegate(Fn fn) : fn_(fn) { }
    template<class T>
    Delegate(T* obj, R (T::*fn)(Args...)) : fn_(FnMemCall<T>(obj, fn)) { }
    template<class T>
    Delegate(T* obj, R (T::*fn)(Args...) const) : fn_(ConstFnMemCall<T>(obj, fn)) { }
    R operator()(Args... args) const {
        return fn_(args...);
    }
};

template<typename R, typename... Args>
Delegate<R, Args...> make_delegate(R(*fn)(Args...)) {
    return Delegate<R, Args...>(fn);
}

template<typename R, typename... Args>
Delegate<R, Args...> make_delegate(std::function<R(Args...)> fn) {
    return Delegate<R, Args...>(fn);
}

template<class T, typename R, typename... Args>
Delegate<R, Args...> make_delegate(T* obj, R(T::*fn)(Args...)) {
    return Delegate<R, Args...>(obj, fn);
}

template<class T, typename R, typename... Args>
Delegate<R, Args...> make_delegate(T* obj, R(T::*fn)(Args...) const) {
    return Delegate<R, Args...>(obj, fn);
}

template<class F>
struct function_traits;
 
template<class R, class... Args>
struct function_traits<R(Args...)> {
    typedef R (*signature)(Args...);
};

template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)> {
};

template <typename FnObj>
struct function_traits : public function_traits<decltype(&FnObj::operator())> {
};

template <typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...)> {
    typedef std::function<R(Args...)> signature;
};

template <typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...) const> {
    typedef std::function<R(Args...)> signature;
};

template <typename FnObj>
typename function_traits<FnObj>::signature to_function (FnObj fnObj) {
    return static_cast<typename function_traits<FnObj>::signature>(fnObj);
}

template<class Fn>
auto make_delegate(Fn fn) -> decltype(make_delegate(to_function(fn))) {
    return make_delegate(to_function(fn));
}
