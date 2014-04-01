// $Id: ChartCell.h,v 1.1.1.1 2013/01/06 16:54:18 braunefe Exp $
// vim:tabstop=2
/***********************************************************************
 Moses - factored phrase-based language decoder
 Copyright (C) 2010 Hieu Hoang

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ***********************************************************************/

#pragma once

#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include "Word.h"
#include "WordsRange.h"
#include "NonTerminal.h"
#include "ChartHypothesis.h"
#include "ChartHypothesisCollection.h"
#include "RuleCube.h"
#include "ChartCellLabelSet.h"

namespace Moses
{
class ChartTranslationOptionList;
class ChartTranslationOptionCollection;
class ChartCellCollection;
class ChartManager;

class ChartCell
{
  friend std::ostream& operator<<(std::ostream&, const ChartCell&);
public:

protected:
  std::map<Word, ChartHypothesisCollection> m_hypoColl;

  WordsRange m_coverage;

  ChartCellLabel *m_sourceWordLabel;
  ChartCellLabelSet m_targetLabelSet;

  bool m_nBestIsEnabled; /**< flag to determine whether to keep track of old arcs */
  ChartManager &m_manager;

public:
  ChartCell(size_t startPos, size_t endPos, ChartManager &manager);
  virtual ~ChartCell();

  virtual void ProcessSentence(const ChartTranslationOptionList &transOptList
                       ,const ChartCellCollection &allChartCells);

  virtual void ProcessSentenceWithSourceLabels(const ChartTranslationOptionList &transOptList
                          ,const ChartCellCollection &allChartCells, const InputType &source, size_t startPos, size_t endPos);

  virtual const HypoList &GetSortedHypotheses(const Word &constituentLabel) const;
  virtual const HypoList* GetAllSortedHypotheses() const;
  virtual bool AddHypothesis(ChartHypothesis *hypo);

  virtual void SortHypotheses();
  virtual void PruneToSize();

  virtual const ChartHypothesis *GetBestHypothesis() const;

  virtual const ChartCellLabel &GetSourceWordLabel() const {
    CHECK(m_coverage.GetNumWordsCovered() == 1);
    return *m_sourceWordLabel;
  }

  virtual const ChartCellLabelSet &GetTargetLabelSet() const {
    return m_targetLabelSet;
  }

  virtual void CleanupArcList();

  virtual void OutputSizes(std::ostream &out) const;
  virtual size_t GetSize() const;

  //! transitive comparison used for adding objects into set
  virtual inline bool operator<(const ChartCell &compare) const {
    return m_coverage < compare.m_coverage;
  }

  virtual void GetSearchGraph(long translationId, std::ostream &outputSearchGraphStream, const std::map<unsigned,bool> &reachable) const;

};

}

