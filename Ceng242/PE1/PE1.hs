module PE1 where

import Text.Printf
import Data.List

-- Type synonyms --
type Point = (Double, Double)
type Signal = (Double, Double, Double, Double)

-- This function takes a Double and rounds it to 2 decimal places as requested in the PE --
getRounded :: Double -> Double
getRounded x = read s :: Double
               where s = printf "%.2f" x

-------------------------------------------------------------------------------------------
----------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------

getDistance :: Point -> Point -> Double
getDistance (x1, y1) (x2, y2) = getRounded (sqrt((x1-x2)^2 + (y1-y2)^2))

-------------------------------------------------------------------------------------------
findAllDistances :: Point -> [Point] -> [Double]
findAllDistances b l = map (getDistance b) l

-------------------------------------------------------------------------------------------

maxNum [x] = x
maxNum (x:x':xs) = maxNum ((if x >= x' then x else x'):xs)


minNum [x] = x
minNum (x:x':xs) = minNum ((if x <= x' then x else x'):xs)

findIndexx b (l:lr) n | b == l = n
                      | otherwise = findIndexx b lr (n+1)

findExtremes :: Point -> [Point] -> (Point, Point)
findExtremes b l = let x = findAllDistances b l; minn = minNum x; maxx = maxNum x; minind = findIndexx minn x 0; maxind = findIndexx maxx x 0; in (l !! minind, l !! maxind)

-------------------------------------------------------------------------------------------
singleAction2 v h | v == 0 && h == 0 = "Stay"
                  | v > 0 && h == 0 = "North"
                  | v < 0 && h == 0 = "South"
                  | v == 0 && h > 0 = "East"
                  | v == 0 && h < 0 = "West"
                  | v > 0 && h > 0 = "NorthEast"
                  | v > 0 && h < 0 = "NorthWest"
                  | v < 0 && h > 0 = "SouthEast"
                  | v < 0 && h < 0 = "SouthWest"

getSingleAction :: Signal -> String
getSingleAction signal = let (north, east, south, west) = signal; vertical = (north - south); horizontal = (east-west) in singleAction2 vertical horizontal

-------------------------------------------------------------------------------------------

getAllActions :: [Signal] -> [String]
getAllActions signals = map (getSingleAction) signals

-------------------------------------------------------------------------------------------
counter (l:lr) act n | length(lr) == 0 && l == act = n+1
                     | length(lr) == 0 && l /= act = n
                     | l == act = counter lr act (n+1)
                     | otherwise = counter lr act n

numberOfGivenAction :: Num a => [Signal] -> String -> a
numberOfGivenAction signals action = let all_actions = getAllActions signals in counter all_actions action 0
