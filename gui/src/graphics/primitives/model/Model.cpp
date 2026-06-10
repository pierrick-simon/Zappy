/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Model.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Graphics {
    Model::Model(const std::string &filePath)
    {
        this->loadFromFile(filePath);
    }

    void Model::loadFromFile(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file)
            throw std::invalid_argument("Failed to open file: " + filePath);

        std::string line;
        for (size_t lineNum = 1; std::getline(file, line); lineNum++) {
            line = line.substr(line.find_first_not_of(' '), line.find('#'));
            std::istringstream iss(line);
            std::string command;
            iss >> command;
            if (!iss)
                throw std::invalid_argument("The command at line " +
                    std::to_string(lineNum) + "is invalid.");
            auto it = LINE_METHODS.find(command);
            if (it != LINE_METHODS.end())
                try {
                    it->second(*this, iss);
                } catch (std::exception &e) {
                    throw std::invalid_argument("Error line " +
                        std::to_string(lineNum) + ": " + e.what());
                }
        }
    }
    const std::vector<Model::VertexType> &Model::getVertices() const
    {
        return this->_vertices;
    }
    const std::vector<Model::TexturePosType> &Model::getTexturePos() const
    {
        return this->_texturePos;
    }
    const std::vector<Face> &Model::getFaces() const
    {
        return this->_faces;
    }

    void Model::parseSingleValuePos(
        std::istringstream &line, double &value, const std::string &posName)
    {
        if (line.eof())
            throw std::invalid_argument("Required value for " + posName);
        line >> value;
        if (!line)
            throw std::invalid_argument("Invalid value for " + posName);
    }

    void Model::parseVertex(std::istringstream &line)
    {
        VertexType vertex;

        parseSingleValuePos(line, vertex.getX(), "vertex x");
        parseSingleValuePos(line, vertex.getY(), "vertex y");
        parseSingleValuePos(line, vertex.getZ(), "vertex z");
        if (!line.eof()) {
            double scale;
            parseSingleValuePos(line, scale, "w");
            vertex *= scale;
        }
        this->_vertices.emplace_back(vertex);
    }
    void Model::parseTexturePos(std::istringstream &line)
    {
        TexturePosType texturePos {0, 0, 0};

        parseSingleValuePos(line, texturePos.getX(), "texture pos x");
        if (!line.eof())
            parseSingleValuePos(line, texturePos.getY(), "texture pos y");
        if (!line.eof())
            parseSingleValuePos(line, texturePos.getZ(), "texture pos z");
        this->_texturePos.emplace_back(texturePos);
    }

    const std::unordered_map<std::string, Model::LineMethod>
        Model::LINE_METHODS = {
            {"v", &Model::parseVertex},
            {"vt", &Model::parseTexturePos},
    };
} // namespace Graphics
