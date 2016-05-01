#ifndef pathFinder_h__
#define pathFinder_h__

#include <vector>
#include "Math/Vector.h"
#include <unordered_map>
#include "world.h"
#include "Debug.h"

struct Path
{
  int length = 0;
  Vec3i *steps;
};

struct node
{
  node()
  {
    parent = Vec3i(0,0,0);
  }
  node(Vec3i _parent, float _StartScore, float _EndScore)
  {
    parent = _parent;
    StartScore = _StartScore;
    EndScore = _EndScore;
  }
  Vec3i parent;
  float StartScore = 0;
  float EndScore = 0;
};


int64_t hash(Vec3i val)
{
  int64_t v = val.x + val.y * 1000 + val.z * 1000 * 1000;
  return v;
}

Vec3i unhash(int64_t val)
{
  int x = val % 1000;
  int y = ((val - x) / 1000) % 1000;
  int z = val / 1000 / 1000;
  return Vec3i(x, y, z);
}

std::unordered_map<int64_t, node> openSet;

std::unordered_map<int64_t, node> closedSet;

int manDist(Vec3i a, Vec3i b)
{
  a -= b;
  return abs(a.x) + abs(a.y) + abs(a.z);
}

int64_t bestScore()
{
  int bestScore = 999999;
  int64_t bestKey;
  for (auto kvp : openSet)
  {
    int score = kvp.second.EndScore + kvp.second.StartScore;
    if (score < bestScore)
    {
      bestScore = score;
      bestKey = kvp.first;
    }
  }
  return bestKey;
}

void AddNeighbour(Vec3i newPos, Vec3i oldPos, Vec3i endPos, node parent)
{
  bool validTile = (World_GetBlock(newPos - Vec3i(0, 1, 0)) > 0) && (World_GetBlock(newPos) == 0);
  if (!validTile) return;
  if (closedSet.count(hash(newPos)) > 0) return;

  int startScore = parent.StartScore + 1;
  if (openSet.count(hash(newPos)) > 0)
  {
    if (openSet[hash(newPos)].StartScore > startScore)
    {
      openSet[hash(newPos)].StartScore = startScore;
      openSet[hash(newPos)].parent = oldPos;
    }
    return;
  }

  openSet.emplace(hash(newPos), node(oldPos, startScore, manDist(newPos, endPos)));

}

Path findPath(Vec3i start, Vec3i end)
{
  openSet.clear();
  closedSet.clear();

  openSet.emplace(hash(start), node(start, 0, manDist(start, end)));

  Path FinalPath;
    
  while (openSet.size() > 0)
  {
    //find lowest gscore
    int64_t currentKey = bestScore();
    node currentNode = openSet[currentKey];

    //return finished path
    if (currentKey == hash(end))
    {
      std::vector<Vec3i> path;
      while (currentKey != hash(start))
      {
        path.push_back(unhash(currentKey));
        currentKey = hash(currentNode.parent);
        currentNode = closedSet[currentKey];
      }
      
      FinalPath.steps = (Vec3i*)malloc(sizeof(Vec3i) * path.size());
      FinalPath.length = path.size();
      int i = 0;
      for (int step = path.size() - 1; step >= 0; step--)
      {
        FinalPath.steps[i++] = path[step];
        Debug_AddFloorLine(path[step] - Vec3i(0, 1, 0), Vec3(1.0, 1.0, 1.0));
      }
      break;
    }

    //Move node to closed set
    openSet.erase(currentKey);
    closedSet.emplace(currentKey, currentNode);

    //Add Neighbours
    AddNeighbour(unhash(currentKey) + Vec3i(1, 0, 0), unhash(currentKey), end, currentNode);
    AddNeighbour(unhash(currentKey) + Vec3i(-1, 0, 0), unhash(currentKey), end, currentNode);
    AddNeighbour(unhash(currentKey) + Vec3i(0, 1, 0), unhash(currentKey), end, currentNode);
    AddNeighbour(unhash(currentKey) + Vec3i(0, -1, 0), unhash(currentKey), end, currentNode);
    AddNeighbour(unhash(currentKey) + Vec3i(0, 0, 1), unhash(currentKey), end, currentNode);
    AddNeighbour(unhash(currentKey) + Vec3i(0, 0, -1), unhash(currentKey), end, currentNode);
    Debug_AddFloorFill(unhash(currentKey) - Vec3i(0, 1, 0), Vec3(0.0, 1.0, 0.0));

  }
  //Failure
  return FinalPath;

}

#endif // pathFinder_h__