#ifndef __LTP_PARSERN_PARSER_FRONTEND_H__
#define __LTP_PARSERN_PARSER_FRONTEND_H__

#include <iostream>

#include "framework/frontend.h"
#include "parser.n/options.h"
#include "parser.n/instance.h"
#include "parser.n/parser.h"
#include "utils/logging.hpp"

namespace ltp {
namespace depparser {

struct PairGreaterBySecond {
  bool operator()(std::pair<int, int> const& l,
      std::pair<int, int> const& r) const {
    if (l.second != r.second) { return l.second > r.second; }
    return l.first < r.first;
  }
};

class NeuralNetworkParserFrontend: public NeuralNetworkParser {
private:
  const LearnOption* learn_opt;
  const TestOption* test_opt;

  std::vector<int> precomputed_features;
  std::vector<Instance*> train_dat;
  std::vector<Instance*> devel_dat;

  std::vector<Sample> dataset;
  size_t cursor;
public:
  //! The learning constructor.
  NeuralNetworkParserFrontend(const LearnOption& opt);

  //! The testing constructor.
  NeuralNetworkParserFrontend(const TestOption& opt);

  ~NeuralNetworkParserFrontend();

  void train(void);
  void test(void);

private:
  bool read_training_data(void);
  void check_dataset(const std::vector<Instance*>& dataset);
  void build_alphabet(void);
  void build_cluster(void);
  void build_feature_space(void);
  void collect_precomputed_features(void);
  void initialize_classifier(void);
  void generate_training_samples_one_batch(
      std::vector<Sample>::const_iterator& begin,
      std::vector<Sample>::const_iterator& end);
  void predict(const Instance& data,
      std::vector<int>& heads,
      std::vector<std::string>& deprels);
};  //  end for class Parser

}   //  end for namespace depparser
}   //  end for namespace ltp

#endif  // end for __LTP_PARSERN_PARSER_H__