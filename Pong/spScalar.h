#pragma once

typedef float spScalar;

__forceinline spScalar Clamp(const spScalar _minValue, const spScalar _maxValue, const spScalar _valueToClamp)
{
	return _valueToClamp < _minValue ? _minValue : _valueToClamp > _maxValue ? _maxValue : _valueToClamp;
}