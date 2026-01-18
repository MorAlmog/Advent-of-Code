#pragma once

template <typename T, std::size_t N>
typename VecND<T,N>::iterator VecND<T,N>::begin() {
    return data.begin();
}

template <typename T, std::size_t N>
typename VecND<T,N>::const_iterator VecND<T,N>::begin() const {
    return data.begin();
}

template <typename T, std::size_t N>
typename VecND<T,N>::iterator VecND<T,N>::end() {
    return data.end();
}

template <typename T, std::size_t N>
typename VecND<T,N>::const_iterator VecND<T,N>::end() const {
    return data.end();
}

template <typename T, std::size_t N>
std::array<T, N>& VecND<T,N>::at(std::size_t arr) {
	return data.at(arr);
}
template <typename T, std::size_t N>
const std::array<T, N>& VecND<T,N>::at(std::size_t arr) const {
	return data.at(arr);
}
template <typename T, std::size_t N>
void VecND<T,N>::erase(const_iterator it) {
	data.erase(it);
}