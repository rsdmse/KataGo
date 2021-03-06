#ifndef PROGRAM_PLAY_UTILS_H_
#define PROGRAM_PLAY_UTILS_H_

#include "../program/play.h"

//This is a grab-bag of various useful higher-level functions that select moves or evaluate the board in various ways.

namespace PlayUtils {
  //Use the given bot to play free handicap stones, modifying the board and hist in the process and setting the bot's position to it.
  //Does NOT switch the initial player of the board history to white
  void playExtraBlack(
    Search* bot,
    int numExtraBlack,
    Board& board,
    BoardHistory& hist,
    double temperature,
    Rand& gameRand
  );

  //Set board to empty and place fixed handicap stones, raising an exception if invalid
  void placeFixedHandicap(Board& board, int n);

  ReportedSearchValues getWhiteScoreValues(
    Search* bot,
    const Board& board,
    const BoardHistory& hist,
    Player pla,
    int64_t numVisits,
    Logger& logger,
    const OtherGameProperties& otherGameProps
  );

  Loc chooseRandomLegalMove(const Board& board, const BoardHistory& hist, Player pla, Rand& gameRand, Loc banMove);
  int chooseRandomLegalMoves(const Board& board, const BoardHistory& hist, Player pla, Rand& gameRand, Loc* buf, int len);

  Loc chooseRandomPolicyMove(
    const NNOutput* nnOutput,
    const Board& board,
    const BoardHistory& hist,
    Player pla,
    Rand& gameRand,
    double temperature,
    bool allowPass,
    Loc banMove
  );

  float roundAndClipKomi(double unrounded, const Board& board, bool looseClipping);

  void adjustKomiToEven(
    Search* botB,
    Search* botW, //can be NULL if only one bot
    const Board& board,
    BoardHistory& hist,
    Player pla,
    int64_t numVisits,
    Logger& logger,
    const OtherGameProperties& otherGameProps,
    Rand& rand
  );

  //Lead from WHITE's perspective
  float computeLead(
    Search* botB,
    Search* botW, //can be NULL if only one bot
    const Board& board,
    BoardHistory& hist,
    Player pla,
    int64_t numVisits,
    Logger& logger,
    const OtherGameProperties& otherGameProps
  );

  double getSearchFactor(
    double searchFactorWhenWinningThreshold,
    double searchFactorWhenWinning,
    const SearchParams& params,
    const std::vector<double>& recentWinLossValues,
    Player pla
  );

  double getHackedLCBForWinrate(const Search* search, const AnalysisData& data, Player pla);

  std::vector<double> computeOwnership(
    Search* bot,
    const Board& board,
    const BoardHistory& hist,
    Player pla,
    int64_t numVisits,
    Logger& logger
  );

  //Determine all living and dead stones, if the game were terminated right now and
  //the rules were interpreted naively and directly.
  //Returns a vector indexed by board Loc (length Board::MAX_ARR_SIZE).
  std::vector<bool> computeAnticipatedStatusesSimple(
    const Board& board,
    const BoardHistory& hist
  );

  //Determine all living and dead stones, trying to be clever and use the ownership prediction
  //of the neural net.
  //Returns a vector indexed by board Loc (length Board::MAX_ARR_SIZE).
  std::vector<bool> computeAnticipatedStatusesWithOwnership(
    Search* bot,
    const Board& board,
    const BoardHistory& hist,
    Player pla,
    int64_t numVisits,
    Logger& logger
  );

}


#endif //PROGRAM_PLAY_UTILS_H_
