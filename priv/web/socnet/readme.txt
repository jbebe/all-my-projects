data structure:
  socnet->
    connect->
      -id ( INT ) 123456 
      -friend ( INT ) 123456 
            
    user->  
      -id [KEY]( INT ) 123456
      -passhash ( STRING ) "9e107d9d372bb6826bd81d3542a419d6"
      -born ( DATE ) 2012.02.11.
      -surname ( STRING ) "Smith"{50}
      -firstname ( STRING ) "Wilson"{50}
      -location ( STRING ) "Hungary,Budapest"
      -other ( STRING(JSON) ) "{tags:'Hungary,Budapest',..}"
            
    wall->
       -id [KEY]( BIGINT ) 2312332432432432432
       -fromid ( INT ) 123456
       -date ( DATETIME ) 2012.02.11.
       -msg ( STRING ) "adsadsadsadsadsadsdadsasad"{1000}
    
    comment->
      -wallid ( BIGINT ) 2312332432432432432
      -fromid ( INT ) 123456
      -date ( DATETIME ) 2012.02.11.
      -msg ( STRING ) "adsadsadsadsadsadsdadsasad"{300}
    
    message->
      -fromid ( INT ) 123456
      -toid ( INT ) 123456
      -date ( DATE ) 2012.02.11.
      -msg ( STRING ) "adsadsadsadsadsadsdadsasad"{1000}
      -seen ( BOOL ) true

USEFUL SQL CMDS:

my friends:

  SELECT user.id, user.lastname, user.firstname, user.born
  FROM user
    LEFT JOIN connect ON connect.friend = user.id
    LEFT JOIN connect as connect2 ON connect2.id = user.id
  WHERE (connect.id = sessionID OR connect.friend = sessionID
    OR connect2.id = sessionID OR connect2.friend = sessionID)
  AND user.id <> sessionID
  ORDER BY user.lastname,user.firstname,user.born ASC

not my friends:
        
  SELECT user.id, user.lastname, user.firstname, user.born
  FROM user
  WHERE user.id NOT IN (
    SELECT user.id
    FROM user
      LEFT JOIN connect ON connect.friend = user.id
      LEFT JOIN connect as connect2 ON connect2.id = user.id
    WHERE (connect.id = sessionID OR connect.friend = sessionID
      OR connect2.id = sessionID OR connect2.friend = sessionID)
    AND user.id <> sessionID)
  AND user.id <> sessionID
  ORDER BY user.lastname,user.firstname,user.born ASC
        
delete friend:

  DELETE
  FROM connect
  WHERE (id = sessionID AND friend = friendID)
    OR (friend = sessionID AND id = friendID)
                
add friend:
        
  INSERT INTO connect (id, friend) VALUES (sessionID,friendID)
  
show wall feed:

  SELECT user.id, user.lastname, user.firstname, wall.msg, wall.date
  FROM wall
    LEFT JOIN user ON user.id = wall.fromid
    LEFT JOIN connect ON connect.friend = user.id
    LEFT JOIN connect as connect2 ON connect2.id = user.id
  WHERE (connect.id = sessionID OR connect.friend = sessionID
    OR connect2.id = sessionID OR connect2.friend = sessionID)
  ORDER BY wall.date DESC
  
USEFUL REGEX

image: (.*)(?:((?:https?\:\/\/)|(?:https?\:\/\/www))[\w\-]+\.[\w]{2,6}(?:\/[\w\-]+)+\.(?:(?:jpe?g)|(?:png)|(?:gif)))(.*)
