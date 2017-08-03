#ifndef GPUSAT_PARSER_H
#define GPUSAT_PARSER_H
#define alloca __builtin_alloca

#include <queue>
#include <types.h>

namespace gpusat {
    class CNFParser {
    public:

        /**
                 * generates a treedec from a given string
                 *
                 * @param formula
                 *      the string representation of the tree decomposition
                 * @return
                 *      the tree decomposition
                 */
        satformulaType parseSatFormula(std::string formula);

    private:
        /**
         * parses a clause line from the sat formula
         *
         * @param item
         *      the line
         * @param clauses
         *      the clauses
         * @param clauseSize
         *      size of each clause
         */
        void parseClauseLine(std::string item, std::queue<std::queue<cl_long>> *clauses, cl_long &clauseSize);

        /**
         * parses a problem line from the sat formula
         *
         * @param satformula
         *      object containing the sat formula
         * @param item
         *      the line
         * @param clauses
         *      object containing the clauses in the sat formula
         */
        void parseProblemLine(satformulaType &satformula, std::string item, std::queue<std::queue<cl_long>> *&clauses);

        int maxWidht;
    };

    class TDParser {
    public:
        TDParser(int i);

        /**
         * generates a treedec from a given string
         *
         * @param graph
         *      the string representation of the tree decomposition
         * @return
         *      the tree decomposition
         */
        treedecType parseTreeDecomp(std::string graph);

    private:
        /**
         * parse an edge from the tree decomposition
         *
         * @param item
         *      the line
         * @param edges
         *      queue containing all edges
         */
        void parseEdgeLine(std::string item, std::queue<cl_long> **edges);

        /**
         * parses the start line from the tree decomposition
         *
         * @param ret
         *      the tree decomposition
         * @param item
         *      the line
         * @param edges
         *      queue containing all edges
         */
        void parseStartLine(preetreedecType &ret, std::string &item, std::queue<cl_long> **&edges);

        /**
         * parses a pag from the tree decomposition
         *
         * @param ret
         *      object containing the tree decomposition
         * @param item
         *      a line from the decomposition
         */
        void parseBagLine(preetreedecType &ret, std::string item);

        void preprocessDecomp(preebagType *decomp);

        int maxWidht;
    };
}
#endif //GPUSAT_PARSER_H
