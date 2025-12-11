#include "abstract_solver.h"

namespace chess_solver
{
	const std::string AbstractSolver::EVALUATION_FILE_NAME = "evaluation.txt";
	
	const std::string AbstractSolver::EVALUATION_WORKING_TIME = "Время решения:";
	
	const std::string AbstractSolver::EVALUATION_ROW_MAX_SEARCH_DEPTH = "D";
	const std::string AbstractSolver::EVALUATION_SOLVE_LENGTH = "L";
	const std::string AbstractSolver::EVALUATION_TOTAL_NODES_COUNT = "N";
	const std::string AbstractSolver::EVALUATION_BRANCHING = "R";
	const std::string AbstractSolver::EVALUATION_TIME = "Время";

	const std::string AbstractSolver::METHOD_DEEP_SEARCH = "Поиск в глубину";
	const std::string AbstractSolver::METHOD_WIDE_SEARCH = "Поиск в ширину";
	const std::string AbstractSolver::METHOD_GRADIENT_SEARCH = "Поиск по градиенту";
	const std::string AbstractSolver::METHOD_BEST_PARTICLE_WAY = "Поиск от наилучшего частичного пути";
	
	
	
    AbstractSolver::~AbstractSolver()
    {
        delete this->tree;
    }

    AbstractSolver::AbstractSolver()
    {
        this->tree = nullptr;
    }

    void AbstractSolver::clearTree()
    {
        if (this->tree)
		{
            delete this->tree;
        }

        this->tree = nullptr;
    }

    void AbstractSolver::initTree(AbstractSituation* startSituation)
    {
        if (tree)
		{
            clearTree();
        }

        this->tree = new OptionTree(startSituation, nullptr, nullptr, 1);
        this->tree->setPotentialMoves(getAllSituationMoves(startSituation));
    }

    OptionTree* AbstractSolver::useDeepSearch(short maximalDepth)
    {
        return deepSearch(this->tree, maximalDepth);
    }

    OptionTree* AbstractSolver::deepSearch(OptionTree* tree, short maximalDepth)
    {
        OptionTree* result = nullptr;

        if (isTargetSituation(tree))
		{
            result = tree;
        }
		else if (!isDeadlock(tree, maximalDepth))
		{
            result = nullptr;

            OptionTree* child = nullptr;

            while (!result && !tree->getCommands()->empty())
			{
                child = createChild(tree);

                if (child)
				{
                    result = deepSearch(child, maximalDepth);

                    tree->insertChild(child);
                }
            }
        }

        return result;
    }

    OptionTree* AbstractSolver::useWideSearch(short maximalDepth)
    {
        std::list<OptionTree*>* rootList = new std::list<OptionTree*>();
        rootList->push_back(this->tree);

        OptionTree* result = wideSearch(rootList, maximalDepth);

        delete rootList;

        return result;
    }

    OptionTree* AbstractSolver::useGradientSearch(short maximalDepth)
    {
        return gradientSearch(this->tree, maximalDepth);
    }

    OptionTree* AbstractSolver::wideSearch(std::list<OptionTree*>* treeLevel, short maximalDepth)
    {
        OptionTree* result = nullptr;

        std::list<OptionTree*>* processedNodes = new std::list<OptionTree*>();

        while (!result && !treeLevel->empty())
		{
            OptionTree* tree = treeLevel->front();

            treeLevel->pop_front();

            if (isTargetSituation(tree))
			{
                result = tree;
            }
			else if (!isDeadlock(tree, maximalDepth))
			{
                processedNodes->push_back(tree);
            }
        }

        if (!result && !processedNodes->empty())
		{
            std::list<OptionTree*>* nextTreeLevel = generateNextTreeLevel(processedNodes, maximalDepth);
            result = wideSearch(nextTreeLevel, maximalDepth);

            delete nextTreeLevel;
        }

        delete processedNodes;

        return result;
    }

    OptionTree* AbstractSolver::gradientSearch(OptionTree* tree, short maximalDepth)
    {
        OptionTree* result = nullptr;

        if (isTargetSituation(tree))
		{
            result = tree;
        }
		else if (!isDeadlock(tree, maximalDepth))
		{
            std::list<OptionTree*>* children = new std::list<OptionTree*>();

            createTreeChildren(tree, children);
            sortNodesByTargetFunction(children);

            while (!result && !children->empty())
			{
                result = gradientSearch(children->front(), maximalDepth);

				children->pop_front();
            }

            delete children;
        }

        return result;
    }

	OptionTree* AbstractSolver::useBestParticalWaySearch(short maximalDepth, int newLevelsCount)
	{
		return bestParticleWaySearch(this->tree, maximalDepth, newLevelsCount);
	}

    OptionTree* AbstractSolver::bestParticleWaySearch(OptionTree* tree, int maximalDepth, int newLevelsCount)
    {
        OptionTree* result = nullptr;

        if (isTargetSituation(tree))
		{
            result = tree;
        }
		else if (!isDeadlock(tree, maximalDepth))
		{
            std::list<OptionTree*> rootLevel;
            rootLevel.push_back(tree);

            std::list<OptionTree*>* nextLevel = generateNextTreeLevel(&rootLevel, maximalDepth);
            std::list<OptionTree*>* nonTarget = new std::list<OptionTree*>();

            while (!result && !nextLevel->empty() && nextLevel->front()->getDepth() != maximalDepth && nextLevel->front()->getDepth() < tree->getDepth() + newLevelsCount)
			{
                for (auto iter = nextLevel->begin(); iter != nextLevel->end() && !result; iter++)
				{
                    if (isTargetSituation(*iter))
					{
                        result = *iter;
                    }
					else if (!isDeadlock(*iter, maximalDepth))
					{
                        nonTarget->push_back(*iter);
                    }
                }

                delete nextLevel;
                nextLevel = generateNextTreeLevel(nonTarget, maximalDepth);
            }

            for (auto iter = nextLevel->begin(); iter != nextLevel->end() && !result; iter++)
			{
                if (isTargetSituation(*iter))
				{
                    result = *iter;
                }
				else if (!isDeadlock(*iter, maximalDepth))
				{
                    nonTarget->push_back(*iter);
                }
            }

			delete nextLevel;
			
			if (!result)
			{
				sortNodesByTargetFunction(nonTarget);
				
				while (!result && !nonTarget->empty())
				{
					result = bestParticleWaySearch(nonTarget->front(), maximalDepth, nonTarget->front()->getDepth() + newLevelsCount);
					
					nonTarget->pop_front();
				}
			}
			
			delete nonTarget;
        }

        return result;
    }

    void AbstractSolver::sortNodesByTargetFunction(std::list<OptionTree*>* nodes)
    {
        std::vector<std::pair<float, OptionTree*>> sorted(nodes->size());

        sorted[0] = std::pair<float, OptionTree*>(evaluationFunction(nodes->front()), nodes->front());

        size_t currentSize = 1;

        auto iter = nodes->begin();
        iter++;

        for (iter; iter != nodes->end(); iter++)
		{
            int ind = 0;

            float funcValue = evaluationFunction(*iter);

            while (funcValue > sorted[ind].first && ind < currentSize)
			{
                ind++;
            }

            for (int i = currentSize - 1; i >= ind; i--)
			{
                sorted[i + 1] = sorted[i];
            }

            sorted[ind] = std::pair<float, OptionTree*>(funcValue, *iter);
            currentSize++;
        }

        nodes->clear();

        for (std::pair<float, OptionTree*> el : sorted)
		{
            nodes->push_back(el.second);
        }
    }

    std::list<OptionTree*>* AbstractSolver::generateNextTreeLevel(std::list<OptionTree*>* treeLevel, short maximalDepth)
    {
        std::list<OptionTree*>* result = new std::list<OptionTree*>();

        while (!treeLevel->empty())
		{
            createTreeChildren(treeLevel->front(), result);

            treeLevel->pop_front();
        }

        return result;
    }

    OptionTree* AbstractSolver::createChild(OptionTree* tree)
    {
        std::list<AbstractCommand*>* commands = tree->getCommands();

        OptionTree* result = nullptr;

        if (!commands->empty())
		{
            AbstractSituation* nextSituation = getNextSituation(tree->getSituation(), commands->front());

            result = new OptionTree(nextSituation, commands->front(), tree, tree->getDepth());
            result->setPotentialMoves(getAllSituationMoves(nextSituation));

            commands->pop_front();
        }

        return result;
    }

    void AbstractSolver::createTreeChildren(OptionTree* tree, std::list<OptionTree*>* children)
    {
        while (!tree->getCommands()->empty())
		{
            OptionTree* child = createChild(tree);

            tree->insertChild(child);
            children->push_back(child);
        }
    }
    
    void AbstractSolver::evaluateAllMethods(AbstractSituation* startSituation, int maximalDepth)
    {
    	using namespace std::chrono;
    	
    	std::ofstream fout(EVALUATION_FILE_NAME);
    	
    	fout << startSituation->toString();
    	
    	fout << std::string(ROW_NAME_LENGTH, ' ');
    	
    	std::string tableTop(ROW_NAME_LENGTH, ' ');
    	
    	tableTop += "|" + makeCellText(CELL_WIDTH, EVALUATION_SOLVE_LENGTH) + "|" + makeCellText(CELL_WIDTH, EVALUATION_ROW_MAX_SEARCH_DEPTH) +
			"|" + makeCellText(CELL_WIDTH, EVALUATION_TOTAL_NODES_COUNT) + "|" + makeCellText(CELL_WIDTH, EVALUATION_BRANCHING) + "|" + makeCellText(CELL_WIDTH, EVALUATION_TIME) + "|\n";
    	
    	fout << tableTop << makeTableSepRow(ROW_NAME_LENGTH, 5, CELL_WIDTH);
    	
    	initTree(startSituation->copy());
    	
    	auto depthSearchStartTime = steady_clock::now();
    	OptionTree* deepSearchResult = useDeepSearch(maximalDepth);
    	auto depthSearchEndTime = steady_clock::now();
    	
    	int deepSearchDuration = duration_cast<seconds>(depthSearchEndTime - depthSearchStartTime).count();
    	
    	size_t deepSearchMaxDepth = calcMaximalOptionTreeDepth(this->tree, 1);
    	size_t deepSearchTotalSize = calcOptionTreeSize(this->tree);
    	short deepSearchSolveDepth = deepSearchResult->getDepth();
    	float deepSearchBranching = static_cast<float>(deepSearchSolveDepth) / deepSearchTotalSize;
    	
    	
    	
    	initTree(startSituation->copy());
    	
    	auto wideSearchStartTime = steady_clock::now();
    	OptionTree* wideSearchResult = useWideSearch(maximalDepth);
    	auto wideSearchEndTime = steady_clock::now();
    	
    	int wideSearchDuration = duration_cast<seconds>(wideSearchEndTime - wideSearchStartTime).count();
    	
    	size_t wideSearchMaxDepth = calcMaximalOptionTreeDepth(this->tree, 1);
    	size_t wideSearchTotalSize = calcOptionTreeSize(this->tree);
    	short wideSearchSolveDepth = wideSearchResult->getDepth();
    	float wideSearchBranching = static_cast<float>(wideSearchSolveDepth) / wideSearchTotalSize;
    	
    	initTree(startSituation->copy());
    	
    	auto gradientSearchStart = steady_clock::now();
    	OptionTree* gradientSearchResult = useGradientSearch(maximalDepth);
    	auto gradientSearchEnd = steady_clock::now();
    	
    	int gradientSearchDuration = duration_cast<seconds>(gradientSearchEnd - gradientSearchStart).count();
    	
    	size_t gradientSearchMaxDepth = calcMaximalOptionTreeDepth(this->tree, 1);
    	size_t gradientSearchTotalSize = calcOptionTreeSize(this->tree);
    	short gradientSearchSolveDepth = gradientSearchResult->getDepth();
    	float gradientSearchBranching = static_cast<float>(gradientSearchSolveDepth) / gradientSearchTotalSize;
    	
    	initTree(startSituation->copy());
    	
    	auto bestParticleWaySearchStartTime = steady_clock::now();
    	OptionTree* bestParticleWaySearchResult = useBestParticalWaySearch(maximalDepth, 2);
    	auto bestParticleWaySearchEndTime = steady_clock::now();
    	
    	int bestParticleWaySearchDuration = duration_cast<seconds>(bestParticleWaySearchEndTime - bestParticleWaySearchStartTime).count();
    	
    	size_t bestParticleWaySearchMaxDepth = calcMaximalOptionTreeDepth(this->tree, 1);
    	size_t bestParticleWaySearchTotalSize = calcOptionTreeSize(this->tree);
    	short bestParticleWaySearchSolveDepth = bestParticleWaySearchResult->getDepth();
    	float brestParticleWaySearchBranching = static_cast<float>(bestParticleWaySearchSolveDepth) / bestParticleWaySearchTotalSize;
    	
    	
	}
	
	short AbstractSolver::calcMaximalOptionTreeDepth(OptionTree* node, short currentMax)
	{
		short result = std::max(node->getDepth(), currentMax);
		
		OptionTree* child = node->getFirstChild();
		
		while (child)
		{
			result = calcMaximalOptionTreeDepth(child, result);
			
			child = node->getNextChild();
		}
		
		return result;
	}
		
	size_t AbstractSolver::calcOptionTreeSize(OptionTree* node)
	{
		size_t result = 1;
		
		OptionTree* child = node->getFirstChild();
		
		while (child)
		{
			result += calcOptionTreeSize(child);
			
			child = node->getNextChild();
		}
		
		return result;
	}
	
	std::string AbstractSolver::makeCellText(int cellWidth, int value)
	{
		std::string valStr = std::to_string(value);
		int ident = (cellWidth - valStr.size()) / 2;
		
		std::string result(ident, ' ');
		
		result += valStr + std::string(cellWidth - ident - valStr.size(), ' ');
		
		return result;
	}
	
	std::string AbstractSolver::buildTableRow(std::string& rowName, int rowNameLength, int cellWidth, int l, int d, int n, int r, int seconds)
	{
		int nameIdent = rowNameLength - rowName.size();
		
		std::string result(nameIdent, ' ');
		result += rowName + std::string(rowNameLength - rowName.size() - nameIdent, ' ');
		result += '|';
		
		result += makeCellText(cellWidth, l) + '|';
		result += makeCellText(cellWidth, d) + '|';
		result += makeCellText(cellWidth, n) + '|';
		result += makeCellText(cellWidth, r) + '|';
		
		std::string timeString = "";
		
		timeString += std::to_string(getHours(seconds)) + ":" + std::to_string(getMinutes(seconds)) + ":" + std::to_string(getRemainingSeconds(seconds));
//		
		result += makeCellText(cellWidth, timeString) + "|\n";
		
		return result;
	}
	
	std::string AbstractSolver::makeTableSepRow(int rowNameLen, int cellsCount, int cellWidth)
	{
		std::string result(rowNameLen, '-');
		
		for (int i = 0; i < cellsCount; i++)
		{
			result += "+" + std::string(cellWidth, '-');
		}
		
		result += "+\n";
		
		return result;
	}
	
	std::string AbstractSolver::makeCellText(int cellWidth, std::string value)
	{
		int ident = (cellWidth - value.size()) / 2;
		
		std::string result(ident, ' ');
		
		result += value + std::string(cellWidth - ident - value.size(), ' ');
		
		return result;
	}
	
	int AbstractSolver::getHours(int totalSeconds)
	{
		return totalSeconds / 3600;
	}
		
	int AbstractSolver::getMinutes(int totalSeconds)
	{
		return (totalSeconds % 3600) / 60;
	}
		
	int AbstractSolver::getRemainingSeconds(int totalSeconds)
	{
		return totalSeconds % 60;
	}
}
