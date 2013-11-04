/*
 * ShardRanker.h
 *
 *  Created on: Oct 23, 2013
 *      Author: yubink
 */

#ifndef SHARDRANKER_H_
#define SHARDRANKER_H_

#include "FeatureStore.h"
#include "indri/Repository.hpp"

using namespace std;

class ShardRanker {
private:
  // array of FeatureStore pointers
  // stores[0] is the whole collection store; stores[1] onwards is each shard; length is numShards+1
  FeatureStore** _stores;

  // a single indri index built the same way; just for stemming term
  indri::collection::Repository* _repo;

  // number of shards
  uint _numShards;

  // Taily parameter used in Eq (11)
  uint _n_c;

  // retrieves the mean/variance for query terms and fills in the given queryMean/queryVar arrays
  void _getQueryFeats(vector<string>& stems, float* queryMean, float* queryVar);

  // tokenizes, stems and stops query term into output vector
  void _getStems(string query, vector<string>* output);

  // calculates All from Eq (10)
  void _getAll(vector<string>& stems, float* all);

public:
  ShardRanker();
  virtual ~ShardRanker();

  void init();
  void rank(string query, vector<pair<int, float> >* ranking);
};

#endif /* SHARDRANKER_H_ */
