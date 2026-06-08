/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef QUATERNION_HPP
    #define QUATERNION_HPP
#include "Vector.hpp"

namespace Maths {
    /**
     * A Rotation Quaternion is a mechanism for representing rotations in three
     * dimensions.
     *
     * It uses 4 real values where 3 represents a direction and the last value
     * represents the rotation around that direction.
     */
    class Quaternion {
    public:
        Quaternion();

        Quaternion(double w, double x, double y, double z);

        bool operator==(const Quaternion &rhs) const;

        bool operator!=(const Quaternion &rhs) const;

        /**
         * Creates new Quaternion representing the rotation of this rotated by
         * \p rhs.
         *
         * As rotations are applied in sequence, it means that \code lhs
         * * rhs\endcode is different from \code rhs * lhs\endcode.
         * @param rhs The right-hand-side Quaternion
         * @return A new Quaternion representing the rotation of this rotated
         * by \p rhs
         */
        Quaternion operator*(const Quaternion &rhs) const;

        /**
         * Rotate the Vector3 point using the current Quaternion.
         * @param point The point to rotate
         * @return The point rotated by the current Quaternion.
         */
        Vector3D operator*(const Vector3D &point) const;

        /**
         * Rotates the current Quaternion by \p rhs.
         * Note that rotations are applied in sequence, so you might need to
         * swap the orders of the Quaternions.
         * @param rhs The right-hand-side Quaternion
         * @return this but rotated.
         */
        Quaternion &operator*=(const Quaternion &rhs);

        /**
         * When normalized, a quaternion keeps the same rotation, but its
         * magnitude is 1.0.
         *
         * As a rotation Quaternion always has a length of 1, this function is
         * mainly used to fix floating-point errors.
         *
         * This method doesn't modify the current Quaternion. Use normalize()
         * if you want to modify it.
         * @return The normalized version of the current Quaternion.
         * @see Quaternion::normalize()
         */
        [[nodiscard]] Quaternion normalized() const;

        /**
         * When normalized, a quaternion keeps the same rotation, but its
         * magnitude is 1.0.
         *
         * As a rotation Quaternion always has a length of 1, this function is
         * mainly used to fix floating-point errors.
         *
         * This method modifies the current Quaternion. Use normalized() if you
         * don't want to modify it.
         * @return The normalized version of the current Quaternion.
         * @see Quaternion::normalized()
         */
        Quaternion &normalize();

        /**
         * This method doesn't modify the current Quaternion. Use inverse() if
         * you want to modify it.
         * @return The inverse of the current Quaternion.
         * @see Quaternion::inverse()
         */
        [[nodiscard]] Quaternion inversed() const;

        /**
         * Inverses the current Quaternion.
         * This method modifies the current Quaternion. Use inversed() if
         * you don't want to modify it.
         * @return The inverse of the current Quaternion.
         * @see Quaternion::inversed()
         */
        Quaternion &inverse();

        /**
         * Converts an input Euler angle rotation specified as three doubles to
         * a Quaternion.
         * @param pitch The Pitch in radians
         * @param roll The Roll in radians
         * @param yaw The Yaw in radians
         * @return A Quaternion converted from an Euler angle rotation.
         */
        static Quaternion fromEuler(double pitch, double roll, double yaw);

        /**
         * Converts an input Euler angle rotation specified as three doubles to
         * a Quaternion.
         * @param pitch The Pitch in degrees
         * @param roll The Roll in degrees
         * @param yaw The Yaw in degrees
         * @return A Quaternion converted from an Euler angle rotation.
         */
        static Quaternion fromEulerDegrees(
            double pitch, double roll, double yaw);

        /**
         * The identity Quaternion means zero rotation.
         * It is mainly used for a default rotation, to reset the rotation,
         * or as a starting point for calculations.
         * @return The identity Quaternion.
         */
        static Quaternion identity();

        [[nodiscard]] double getW() const;

        [[nodiscard]] double getX() const;

        [[nodiscard]] double getY() const;

        [[nodiscard]] double getZ() const;

    private:
        [[nodiscard]] double magnitude() const;

        double _w;
        double _x;
        double _y;
        double _z;
    };

    std::ostream &operator<<(
        std::ostream &stream, const Quaternion &quaternion);

    Vector3D &operator*=(Vector3D &vector, const Quaternion &rotation);

    Vector3D operator*(const Vector3D &point, const Quaternion &rotation);
} // namespace Maths

#endif
