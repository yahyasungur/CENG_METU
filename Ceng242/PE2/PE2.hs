module PE2 where

import Text.Printf

type Point = (Int, Int)
type Dimensions = (Int, Int)
type Vector = (Int, Int)

getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

castIntToDouble x = (fromIntegral x) :: Double

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------
getVector :: String -> Vector
getVector d | d == "Stay" = (0,0)
            | d == "North" = (0,1)
            | d == "South" = (0,-1)
            | d == "East" = (1,0)
            | d == "West" = (-1,0)
            | d == "NorthEast" = (1,1)
            | d == "NorthWest" = (-1,1)
            | d == "SouthEast" = (1,-1)
            | d == "SouthWest" = (-1,-1)

-------------------------------------------------------------------------------------------------------------------------------
getAllVectors :: [String] -> [Vector]
getAllVectors l = map (getVector) l

-------------------------------------------------------------------------------------------------------------------------------
helperProducePath (x,y) vec lst | length(vec) == 0 = lst
                                | otherwise = let (x2,y2) = vec !! 0;; lastpoint = (x+x2,y+y2); list = lst ++ [lastpoint]; rest = tail vec; in helperProducePath lastpoint rest list
                                
producePath :: Point -> [String] -> [Point]
producePath initial actions = let acts = getAllVectors actions in helperProducePath initial acts [initial]

-------------------------------------------------------------------------------------------------------------------------------

helper (x,y) rest (bx,by) lst | length(rest) == 0 && x < bx && x >= 0 && y < by && y >= 0  = lst ++ [(x,y)]
                              | length(rest) == 0 = lst
                              | x >= bx || x < 0 || y >= by || y < 0 = lst
                              | otherwise = let list = lst ++ [(x,y)]; (x1,y1) = rest !! 0; re = tail rest in helper (x1,y1) re (bx,by) list

takePathInArea :: [Point] -> Dimensions -> [Point]
takePathInArea path (bx, by) = let (x,y) = path !! 0; rest = tail path in helper (x, y) rest (bx, by) []

-------------------------------------------------------------------------------------------------------------------------------

helper2 pointsRobotPass point rest lst | length(rest) == 0 && (point `elem` pointsRobotPass) == False = lst ++ [point]
                                       | length(rest) == 0 = lst
                                       | (point `elem` pointsRobotPass) == False = let pnt = rest !! 0; re = tail rest; list = lst ++ [point] in helper2 pointsRobotPass pnt re list
                                       | otherwise = let pnt = rest !! 0; re = tail rest in helper2 pointsRobotPass pnt re lst

remainingObjects :: [Point] -> Dimensions -> [Point] -> [Point]
remainingObjects path border objects = let pointsRobotPass = takePathInArea path border; point = objects !! 0; rest = tail objects in helper2 pointsRobotPass point rest []

-------------------------------------------------------------------------------------------------------------------------------

helper3 path rest border objects lst | length(rest) == 0 && (remainingObjects path border objects) == [] && length(takePathInArea path border) == length(path) = lst ++ [path]
                                     | length(rest) == 0 = lst
                                     | (remainingObjects path border objects) == [] && length(takePathInArea path border) == length(path) = let list = lst ++ [path]; pth = rest !! 0; re = tail rest in helper3 pth re border objects list
                                     | otherwise = let pth = rest !! 0; re = tail rest in helper3 pth re border objects lst

helper4 p pr n | length(pr) == 0 = n + length(p)
               | otherwise = let path = pr !! 0; rest = tail pr; number = n + length(p) in helper4 path rest number

averageStepsInSuccess :: [[Point]] -> Dimensions -> [Point] -> Double
averageStepsInSuccess paths border objects = let path = paths !! 0; rest = tail paths; successful_paths =  helper3 path rest border objects []; p = successful_paths !! 0; pr = tail successful_paths; total_steps = helper4 p pr 0; ts = castIntToDouble total_steps; suc_p_n = castIntToDouble (length(successful_paths)) in ts / suc_p_n
