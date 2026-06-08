/*
** EPITECH PROJECT, 2026
** day10
** File description:
** DESCRIPTION
*/

#ifndef MATRIX_HPP
    #define MATRIX_HPP
    #include <array>
    #include <concepts>
    #include <cstddef>
    #include <ostream>
    #include <utility>

namespace Maths {
    template<typename A, typename B>
    concept Multipliable = requires(A a, B b) {
        { a * b };
    };

    template<typename T>
    concept AddAssignable = requires(T a, T b) {
        { a += b } -> std::same_as<T &>;
    };

    template<typename A, typename B>
    concept Addable = requires(A a, B b) {
        { a + b };
    };

    template<typename T, typename S>
    concept MultiplyAssignable = requires(T a, S b) {
        { a *= b } -> std::same_as<T &>;
    };

    template<typename T, typename S>
    concept DivideAssignable = requires(T a, S b) {
        { a /= b } -> std::same_as<T &>;
    };

    template<typename T, typename U>
    concept AssignableFrom = requires(T a, U b) { a = b; };

    template<std::size_t NbRow, std::size_t NbColumn, typename Type>
    class Matrix {
    public:
        using MatrixType = std::array<std::array<Type, NbColumn>, NbRow>;

        explicit Matrix() :
            _matrix {}
        {
        }

        explicit Matrix(Type defaultValue)
            requires(NbRow *NbColumn != 1)
        {
            for (std::size_t x = 0; x < NbRow; ++x)
                for (std::size_t y = 0; y < NbColumn; ++y)
                    this->_matrix[x][y] = defaultValue;
        }

        explicit Matrix(MatrixType matrix) :
            _matrix(matrix)
        {
        }

        const Type &operator()(std::size_t row, std::size_t col) const
        {
            return this->_matrix[row][col];
        }

        Type &operator()(std::size_t row, std::size_t col)
        {
            return this->_matrix[row][col];
        }

        template<typename... Args>
            requires(sizeof...(Args) == NbRow * NbColumn)
        explicit Matrix(Args &&...args)
        {
            std::array<Type, NbRow * NbColumn> values {
                static_cast<Type>(args)...};

            for (std::size_t row = 0; row < NbRow; ++row)
                for (std::size_t col = 0; col < NbColumn; ++col)
                    this->_matrix[row][col] = values[row * NbColumn + col];
        }

        template<class OtherType>
        using ProductType =
            decltype(std::declval<Type>() * std::declval<OtherType>());

        template<class OtherType>
        using AdditionType =
            decltype(std::declval<Type>() + std::declval<OtherType>());

        template<class OtherType>
        using SubtractionType =
            decltype(std::declval<Type>() - std::declval<OtherType>());

        template<class OtherType>
        using DivisionType =
            decltype(std::declval<Type>() / std::declval<OtherType>());

        template<typename OtherType>
            requires Addable<Type, OtherType>
        Matrix<NbRow, NbColumn, AdditionType<OtherType>> operator+(
            const Matrix<NbRow, NbColumn, OtherType> &other) const
        {
            Matrix<NbRow, NbColumn, AdditionType<OtherType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) + other(i, j);
            return result;
        }

        template<typename OtherType>
            requires Addable<Type, OtherType>
        Matrix<NbRow, NbColumn, SubtractionType<OtherType>> operator-(
            const Matrix<NbRow, NbColumn, OtherType> &other) const
        {
            Matrix<NbRow, NbColumn, SubtractionType<OtherType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) - other(i, j);
            return result;
        }

        template<std::size_t OtherNbColumn, class OtherType>
            requires Multipliable<Type, OtherType> &&
            AddAssignable<ProductType<OtherType>> &&
            std::default_initializable<ProductType<OtherType>>
        Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> operator*(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other) const
        {
            Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> result(
                ProductType<OtherType> {});
            for (std::size_t i = 0; i < NbRow; ++i) {
                calculateLine<OtherNbColumn, OtherType>(other, result, i);
            }
            return result;
        }

        template<std::size_t OtherNbColumn, typename OtherType>
        Matrix &operator*=(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other)
        {
            *this = *this * other;
            return *this;
        }

        template<typename ScalarType>
            requires Multipliable<Type, ScalarType>
        Matrix operator*(const ScalarType &scalar) const
        {
            Matrix result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) * scalar;
            return result;
        }

        template<typename ScalarType>
            requires Multipliable<Type, ScalarType>
        Matrix &operator*=(const ScalarType &scalar)
            requires MultiplyAssignable<Type, ScalarType>
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) *= scalar;
            return *this;
        }

        template<typename ScalarType>
            requires Multipliable<Type, ScalarType>
        Matrix<NbRow, NbColumn, DivisionType<ScalarType>> operator/(
            const ScalarType &scalar) const
        {
            Matrix<NbRow, NbColumn, DivisionType<ScalarType>> result;

            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) / scalar;
            return result;
        }

        template<typename ScalarType>
            requires Multipliable<Type, ScalarType>
        Matrix &operator/=(const ScalarType &scalar)
            requires DivideAssignable<Type, ScalarType>
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) /= scalar;
            return *this;
        }

        [[nodiscard]] bool operator==(const Matrix &other) const
        {
            return this->getMatrix() == other.getMatrix();
        }

        [[nodiscard]] bool operator!=(const Matrix &other) const
        {
            return !(*this == other);
        }

        template<typename ScalarType>
            requires Addable<Type, ScalarType> &&
            AssignableFrom<Type, AdditionType<ScalarType>>
        Matrix operator+(const ScalarType &scalar) const
        {
            Matrix result;
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) + scalar;
            return result;
        }

        template<typename ScalarType>
            requires Addable<Type, ScalarType> &&
            AssignableFrom<Type, SubtractionType<ScalarType>>
        Matrix<NbRow, NbColumn, SubtractionType<ScalarType>> operator-(
            const ScalarType &scalar) const
        {
            Matrix<NbRow, NbColumn, SubtractionType<ScalarType>> result;
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    result(i, j) = (*this)(i, j) - scalar;
            return result;
        }

        template<typename ScalarType>
            requires Addable<Type, ScalarType> &&
            AssignableFrom<Type, AdditionType<ScalarType>>
        Matrix &operator+=(const ScalarType &scalar)
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) = (*this)(i, j) + scalar;
            return *this;
        }

        template<typename ScalarType>
            requires Addable<Type, ScalarType> &&
            AssignableFrom<Type, SubtractionType<ScalarType>>
        Matrix &operator-=(const ScalarType &scalar)
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) = (*this)(i, j) - scalar;
            return *this;
        }

        template<typename OtherType>
            requires Addable<Type, OtherType> &&
            AssignableFrom<Type, AdditionType<OtherType>>
        Matrix &operator+=(const Matrix<NbRow, NbColumn, OtherType> &other)
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) = (*this)(i, j) + other(i, j);
            return *this;
        }

        template<typename OtherType>
            requires Addable<Type, OtherType> &&
            AssignableFrom<Type, SubtractionType<OtherType>>
        Matrix &operator-=(const Matrix<NbRow, NbColumn, OtherType> &other)
        {
            for (std::size_t i = 0; i < NbRow; ++i)
                for (std::size_t j = 0; j < NbColumn; ++j)
                    (*this)(i, j) = (*this)(i, j) - other(i, j);
            return *this;
        }

        [[nodiscard]] const std::array<std::array<Type, NbColumn>, NbRow> &getMatrix() const
        {
            return this->_matrix;
        }

    private:
        MatrixType _matrix;

        template<std::size_t OtherNbColumn, class OtherType>
            requires Multipliable<Type, OtherType> &&
            AddAssignable<ProductType<OtherType>> &&
            std::default_initializable<ProductType<OtherType>>
        void calculateLine(
            const Matrix<NbColumn, OtherNbColumn, OtherType> &other,
            Matrix<NbRow, OtherNbColumn, ProductType<OtherType>> &result,
            std::size_t i) const
        {
            for (std::size_t j = 0; j < OtherNbColumn; ++j) {
                result(i, j) = ProductType<OtherType> {};
                for (std::size_t k = 0; k < NbColumn; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
    };

    template<std::size_t NbRow, std::size_t NbColumn, typename Type>
    std::ostream &operator<<(
        std::ostream &input, const Matrix<NbRow, NbColumn, Type> &matrix)
    {
        input << "[";
        for (std::size_t i = 0; i < NbRow; ++i) {
            input << "[";
            for (std::size_t j = 0; j < NbColumn; ++j) {
                input << matrix.getMatrix()[i][j];
                if (j + 1 != NbColumn)
                    input << ", ";
            }
            input << "]";
            if (i + 1 != NbRow)
                input << ", ";
        }
        input << "]";
        return input;
    }

    template<size_t NbRow, size_t NbColumn>
    using MatrixD = Matrix<NbRow, NbColumn, double>;
} // namespace Maths

#endif
