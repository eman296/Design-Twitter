class Twitter 
{
    private:
            unordered_map<int, vector<pair<int,int>>> user_tweets;
            unordered_map<int, unordered_set<int>> user_follows;
            int timestamp;
public:
    Twitter() 
    {
        timestamp=0;
    }
    
    void postTweet(int userId, int tweetId) 
    {
        user_tweets[userId].emplace_back(timestamp++, tweetId);
    }
    
    vector<int> getNewsFeed(int userId) 
    {
        vector<pair<int,int>> newsfeed;
        priority_queue<pair<int, int>> maxHeap;  // Max heap to get the most recent tweets.
        
        
        for(auto &tweet: user_tweets[userId])
        {
            maxHeap.push(tweet);
        }
        
         for (int followeeId : user_follows[userId]) 
         {
            for (auto& tweet : user_tweets[followeeId]) 
            {
                maxHeap.push(tweet);
            }
        }
        
        vector<int> result;
        
        while (!maxHeap.empty() && result.size() < 10) 
        {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        
        return result;
        
    }
    
    void follow(int followerId, int followeeId) 
    {
        if(followerId!=followeeId)
        {
            user_follows[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) 
    {
        user_follows[followerId].erase(followeeId);
    }
};
