/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef SHADER_HPP
    #define SHADER_HPP
    #include <Shader.hpp>
    #include <Vector3.hpp>
    #include <unordered_map>

namespace Graphics {

    class Shader : public raylib::Shader {
    public:
        using raylib::Shader::Shader;

        template<typename... Args>
        void setValue(const std::string &name, Args... args)
        {
            this->SetValue(this->getLocation(name), args...);
        }

        void setValue(const std::string &name, const ::Vector3 &vector);

        void setValue(const std::string &name, const ::Vector4 &vector);

        int getLocation(const std::string &name);

    private:
        std::unordered_map<std::string, int> _locations;
    };

} // namespace Graphics

#endif
