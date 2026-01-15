#pragma once

template <typename T>
typename Vec2D<T>::iterator Vec2D<T>::begin() {
    return data.begin();
}

template <typename T>
typename Vec2D<T>::const_iterator Vec2D<T>::begin() const {
    return data.begin();
}

template <typename T>
typename Vec2D<T>::iterator Vec2D<T>::end() {
    return data.end();
}

template <typename T>
typename Vec2D<T>::const_iterator Vec2D<T>::end() const {
    return data.end();
}


template <typename T>
const std::array<T, 2>& Vec2D<T>::at(std::size_t r) const {
	return data.at(r);
}
template <typename T>
void Vec2D<T>::erase(const_iterator it) {
	data.erase(it);
}