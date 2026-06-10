/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef MODEL_HPP
    #define MODEL_HPP
    #include <functional>
    #include <unordered_map>
    #include <vector>

    #include "Face.hpp"

namespace Graphics {
    class Model {
    public:
        explicit Model(const std::string &filePath);
        void loadFromFile(const std::string &filePath);

        using VertexType = Maths::Vector3D;
        using TexturePosType = Maths::Vector3D;
        using NormalType = Maths::Vector3D;

        [[nodiscard]] const std::vector<VertexType> &getVertices() const;
        [[nodiscard]] const std::vector<TexturePosType> &getTexturePos() const;
        [[nodiscard]] const std::vector<NormalType> &getNormals() const;
        [[nodiscard]] const std::vector<Face> &getFaces() const;

    private:
        static void parseSingleValuePos(std::istringstream &line, double &value,
            const std::string &posName);
        void parseVertex(std::istringstream &line);
        void parseTexturePos(std::istringstream &line);
        void parseNormal(std::istringstream &line);

        std::vector<VertexType> _vertices;
        std::vector<TexturePosType> _texturePos;
        std::vector<NormalType> _normals;
        std::vector<Face> _faces;

        using LineMethod =
            std::function<void(Model &model, std::istringstream &line)>;
        static const std::unordered_map<std::string, LineMethod> LINE_METHODS;
    };
} // namespace Graphics

#endif
