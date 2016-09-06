#ifndef BITFIELD_H
#define BITFIELD_H

#define DECLARE_BITFIELD(type_) \
    constexpr bool is_bitfield(type_) { return true; } \
    using bitfield::operator|; \
    using bitfield::operator|=; \
    using bitfield::operator&; \
    using bitfield::operator&=; \
    using bitfield::operator^; \
    using bitfield::operator^=; \
    using bitfield::operator~

namespace bitfield {

template <class T>
constexpr bool is_bitfield(T) { return false; }

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type&
operator|=(T& lhs, T rhs) {
	using underlying = typename std::underlying_type<T>::type;
	return lhs = static_cast<T>(
		static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type
operator|(T lhs, T rhs) {
	return lhs |= rhs;
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type&
operator&=(T& lhs, T rhs) {
	using underlying = typename std::underlying_type<T>::type;
	return lhs = static_cast<T>(
		static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type
operator^(T lhs, T rhs) {
	return lhs ^= rhs;
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type&
operator^=(T& lhs, T rhs) {
	using underlying = typename std::underlying_type<T>::type;
	return lhs = static_cast<T>(
		static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type
operator&(T lhs, T rhs) {
	return lhs &= rhs;
}

template <class T>
constexpr typename std::enable_if<is_bitfield(T()), T>::type
operator~(T lhs) {
	using underlying = typename std::underlying_type<T>::type;
	return static_cast<T>(~static_cast<underlying>(lhs));
}

} // namespace bitfield

#endif // BITFIELD_H
