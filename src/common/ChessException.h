/*
 * @file ChessException.h
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */
#include <iostream>
#include <string>

/**
 * @brief A class of a custom exception
 *
 */
class ChessException : public std::runtime_error
{
  public:
    /**
     * @brief Construct a new Chess Exception object
     *
     * @param error The description of why the exception is thrown
     */
    ChessException(const std::string &error)
        : std::runtime_error(std::string("EXCEPTION THROWN: ") + error) {}
};