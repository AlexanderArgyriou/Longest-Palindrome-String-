class Solution 
{
    public:
        inline int longestPalindrome( std::string s ) const noexcept
        {   
            std::string                     ans("");
            std::unordered_map<char, int> U_HashMap;
            std::multimap<int, char>    HashMap_Odd;
            
            // Traverse the string and create a Map, where Keys is string's characters , and Values 
            // are the number of character's appearances in the string ex. (C -> 4, A -> 3, B -> 1)
            std::for_each( s.begin(), s.end(), [&U_HashMap](const auto &C) -> void
                          {
                              if( U_HashMap.find(C) == U_HashMap.end() )
                                  U_HashMap.insert( pair<char,int>(C, 1) );
                              else
                                  U_HashMap.find(C)->second++;
                          } );  // for_each
            
            // Traverse The Map, if The Number of a character's appearances are even, add half of characters
            // in the start , and the other half in the end of the answer, so answer remains palindrome
            // ex. (a -> 4), ans += aa...aa, if appearances are odd, add a pair to another multimap which 
            // keeps the appearances as keys and the characters as values, so u can have them in ascending 
            // order. add the first odd number of characters in the middle of string and all the others
            // make them even with substarct 1 and follow the techique for even numbers.
            // Algo guarantee's the biggest Palindrome String.
            std::for_each( U_HashMap.begin(), U_HashMap.end(), [&HashMap_Odd, &ans](const auto &P) -> void
                          {
                              if( !(P.second % 2) )
                              {
                                  ans.insert(ans.begin(), P.second / 2, P.first );
                                  ans.insert(ans.end(), P.second / 2, P.first );
                              } // if
                              else
                                  HashMap_Odd.insert(  pair<int,char>(P.second, P.first) );
                          } );  // for_each
            
            if( HashMap_Odd.size() )
            {
                auto Itr = HashMap_Odd.begin();
                ans.insert( ans.begin() + ans.length() / 2, Itr->first,  Itr->second );
                Itr++;
                
                while( Itr != HashMap_Odd.end() )
                {
                    ans.insert(ans.begin(), Itr->first / 2, Itr->second );
                    ans.insert(ans.end(), Itr->first / 2, Itr->second );
                    Itr++;
                }   // while
            }   // if
            
            return ans.length();
        }   // longestPalindrome
};  // Solution 
