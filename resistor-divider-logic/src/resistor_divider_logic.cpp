// https://github.com/dsabala/resistor-divider
// License: MIT

#include <resistor-divider-logic/resistor_divider_logic.hpp>
#include <pairs_finder.hpp>

namespace ResistorDivider
{
    
SearchResults Search(SearchCriteria & criteria)
{
    SearchResults results;

    if(!(CheckCriteria(criteria)))
    {
        results.criteria_is_correct = false;
        return results;
    }

    //std::vector<ResistorsPair> pairs_list;
    //PairsFinder::GenerateRatioList(pairs_list, );
    //return pairs_list;

    return results;
}

bool CheckCriteria(SearchCriteria & criteria)
{
    if(kCriteriaSeriesAllowes.count(criteria.res_e_serie) == 0)
    {
        return false;
    }

    if((criteria.ratio < kCriteriaRatioMin) || (criteria.ratio > kCriteriaRadioMax))
    {
        return false;
    }

    return true;
}

}