/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Quaternion.hpp"

#include <cmath>

#include "Utils.hpp"

namespace Maths {
    bool Quaternion::operator==(const Quaternion &rhs) const
    {
        return this->_w == rhs._w && this->_x == rhs._x && this->_y == rhs._y &&
            this->_z == rhs._z;
    }

    bool Quaternion::operator!=(const Quaternion &rhs) const
    {
        return !(*this == rhs);
    }

    Quaternion Quaternion::operator*(const Quaternion &rhs) const
    {
        return {this->_w * rhs._w - this->_x * rhs._x - this->_y * rhs._y -
                this->_z * rhs._z,
            this->_w * rhs._x + this->_x * rhs._w + this->_y * rhs._z -
                this->_z * rhs._y,
            this->_w * rhs._y - this->_x * rhs._z + this->_y * rhs._w +
                this->_z * rhs._x,
            this->_w * rhs._z + this->_x * rhs._y - this->_y * rhs._x +
                this->_z * rhs._w};
    }

    Vector3D Quaternion::operator*(const Vector3D &point) const
    {
        Quaternion pointQuat {0, point.getX(), point.getY(), point.getZ()};

        Quaternion result = *this * pointQuat * this->inversed();

        return Vector3D {result._x, result._y, result._z};
    }

    Quaternion &Quaternion::operator*=(const Quaternion &rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    Quaternion Quaternion::normalized() const
    {
        double magnitude = this->magnitude();

        if (magnitude < 1e-10)
            return identity();

        return {
            this->_w / magnitude,
            this->_x / magnitude,
            this->_y / magnitude,
            this->_z / magnitude,
        };
    }

    Quaternion &Quaternion::normalize()
    {
        double magnitude = this->magnitude();

        if (magnitude < 1e-10) {
            *this = identity();
            return *this;
        }

        this->_w /= magnitude;
        this->_x /= magnitude;
        this->_y /= magnitude;
        this->_z /= magnitude;
        return *this;
    }

    Quaternion Quaternion::inversed() const
    {
        double magnitudeSquared = this->_w * this->_w + this->_x * this->_x +
            this->_y * this->_y + this->_z * this->_z;

        if (magnitudeSquared < 1e-10)
            return identity();

        return {this->_w / magnitudeSquared,
            -this->_x / magnitudeSquared,
            -this->_y / magnitudeSquared,
            -this->_z / magnitudeSquared};
    }

    Quaternion &Quaternion::inverse()
    {
        *this = this->inversed();
        return *this;
    }

    Quaternion Quaternion::fromEuler(double pitch, double roll, double yaw)
    {
        double halfU = pitch / 2.0;
        double halfV = roll / 2.0;
        double halfW = yaw / 2.0;

        double cosU = std::cos(halfU);
        double cosV = std::cos(halfV);
        double cosW = std::cos(halfW);

        double sinU = std::sin(halfU);
        double sinV = std::sin(halfV);
        double sinW = std::sin(halfW);

        return Quaternion {cosU * cosV * cosW + sinU * sinV * sinW,
            sinU * cosV * cosW - cosU * sinV * sinW,
            cosU * sinV * cosW + sinU * cosV * sinW,
            cosU * cosV * sinW - sinU * sinV * cosW}
            .normalized();
    }

    Quaternion Quaternion::fromEulerDegrees(
        double pitch, double roll, double yaw)
    {
        return fromEuler(toRadians(pitch), toRadians(roll), toRadians(yaw));
    }

    std::array<double, 16> Quaternion::toGlMatrix() const
    {
        double xSquared = this->getX() * this->getX();
        double ySquared = this->getY() * this->getY();
        double zSquared = this->getZ() * this->getZ();
        double xw = this->_x * this->_w;
        double xy = this->_x * this->_y;
        double xz = this->_x * this->_z;
        double yw = this->_y * this->_w;
        double yz = this->_y * this->_z;
        double zw = this->_z * this->_w;

        return {
            1 - 2 * (ySquared + zSquared), 2 * (xy + zw), 2 * (xz - yw), 0,
            2 * (xy - zw), 1 - 2 * (xSquared + zSquared), 2 * (yz + xw), 0,
            2 * (xz + yw), 2 * (yz - xw), 1 - 2 * (xSquared + ySquared), 0,
            0, 0, 0, 1
        };
    }

    Quaternion Quaternion::identity()
    {
        return {1, 0, 0, 0};
    }

    double Quaternion::getW() const
    {
        return this->_w;
    }

    double Quaternion::getX() const
    {
        return this->_x;
    }

    double Quaternion::getY() const
    {
        return this->_y;
    }

    double Quaternion::getZ() const
    {
        return this->_z;
    }

    Quaternion::Quaternion() :
        Quaternion(identity())
    {
    }

    Quaternion::Quaternion(double w, double x, double y, double z) :
        _w(w), _x(x), _y(y), _z(z)
    {
    }

    double Quaternion::magnitude() const
    {
        return std::sqrt(this->_w * this->_w + this->_x * this->_x +
            this->_y * this->_y + this->_z * this->_z);
    }

    std::ostream &operator<<(std::ostream &stream, const Quaternion &quaternion)
    {
        stream << "Quaternion{" << quaternion.getW() << ", ";
        stream << quaternion.getX() << ", ";
        stream << quaternion.getY() << ", ";
        stream << quaternion.getZ() << "}";
        return stream;
    }

    Vector3D &operator*=(Vector3D &vector, const Quaternion &rotation)
    {
        vector = rotation * vector;
        return vector;
    }

    Vector3D operator*(const Vector3D &point, const Quaternion &rotation)
    {
        Vector3D point1(point);
        point1 *= rotation;
        return point1;
    }
} // namespace Maths
