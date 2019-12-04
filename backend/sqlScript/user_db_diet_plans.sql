-- MySQL dump 10.13  Distrib 8.0.17, for Win64 (x86_64)
--
-- Host: localhost    Database: user_db
-- ------------------------------------------------------
-- Server version	8.0.17

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `diet_plans`
--

DROP TABLE IF EXISTS `diet_plans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `diet_plans` (
  `diet_plan_id` int(11) NOT NULL,
  `calorie_count` int(11) NOT NULL,
  `dietary_restrictions` int(11) NOT NULL,
  `breakfast` varchar(250) NOT NULL,
  `lunch` varchar(250) NOT NULL,
  `dinner` varchar(250) NOT NULL,
  PRIMARY KEY (`diet_plan_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `diet_plans`
--

LOCK TABLES `diet_plans` WRITE;
/*!40000 ALTER TABLE `diet_plans` DISABLE KEYS */;
INSERT INTO `diet_plans` VALUES (100,1614,0,'2 Eggs, 4 Strips Bacon, 2 Slices of Bread','1.5 Cup Chicken, 1 Cup Rice, 1 Cup Brocolli','1.5 Cup Fettuccine Alfredo, 2 Cups Salad, Slice of Bread'),(101,1212,0,'3 Eggs, 2 Slices of Bread, 2 Cups of Cereal','2 Slices of Bread, Can of Tuna, 2 Slices Cheese','1 Cup Chicken,1 Baked Potato,1 Cup Green Beans'),(102,1600,0,'1 Cup Oatmeal,1 Cup  Blueberries,3 Tbsp Peanut Butter','2 Slices Bread, 1 Slice Turkey, 1 Slice Cheese, 2 tbsp Mustard','1 Fillet Salmon, 1 Cup Brown Rice,1 Cup Broccoli'),(103,1606,0,'1 Cup Cottage Cheese, 1/2 Pineapple','3 Oz Ground Beef,1 Cup Rice, 1 Cup Black Beans','1 Cup Chicken, 1 Cup Mashed Potatoes, 6 Tomato Slices'),(104,1540,0,'1 Sausage, 2 Biscuits, 1/2 cup Gravy','1 Slice Salami, 1 Slice Ham, 2 Slices of Bread, 2 Tsp, Mayo, 3 Pieces Lettuce','8 Oz Steak, 1 Cup Rice, 1 Cup Sweet peas'),(105,1348,1,'4 Strips Tempeh Bacon, 1 Sauteed Mushrooms, 1 Cup Avocado','1 Cup Whole-Grain Pasta, 8 Lentil Balls, 2 Cups Salad','1 Cauliflower and 1/2 Cup Chickpea tacos, 1/2 Cup Guacamole, 1/2 Cup Pico de Gallo'),(106,1281,1,'1 Cup Coconut Yogurt, 1/2 Cup Blueberries, 1/2 Cup Walnuts, 1/2 Cup Chia Seeds','1 Cup Baked Tofu, 1 Cup Sauteed Red Cabbage, 1 Cup Brussel Sprouts, 1/2 Cup Chick Peas','2 Cups Bean Salad (Black-Eyed Peas, Tomatoes, Corn, Bell Peppers, Onions'),(107,1404,2,'2 Slices Whole Wheat Toast, 1 Cup Avocado, 1/2 Cup Nutritional Yeast','1/2 Cup Grilled Veggies and Hummus Spinach Wrap, 1 Cup Sweet Potato Fries','3/4 Cup Chickpea Curry, 1 Cup Basmati Rice'),(108,1306,2,'1 Cup oatmeal, .5 Cup Skim Milk, 1 Diced Apple, 2 Tbsp Walnuts, 2 Tbsp. Peanut Butter','2 Cups Green salad with Chickpeas, 1/2 Cucumber, 1/2 Tomato. 1 Tbsp Cottage Cheese,1 Cup Yogurt','1/2 Cup Bean and 3/4 Cup Veggie Taco Bowl, 1/2 Cup Salsa, 1oz Shredded Cheese, 1/2 Bell pepper, 1/2 onion, 1/2 Cup Brown Rice'),(109,1513,3,'1 Cup Gluten Free Oats, 1/2 Cup Blueberries, 2 Tbsp Sliced Almonds, Drizzle of Honey','2 Corn Tortillas, 1/4 Cup Cheese, 1/2 Cup Avocado, 1/2 Medium Bell Pepper, 1/4 Cup Salsa','Chickpea and Potato Hash, 1 Slice Gluten Free Toast, 2 Cups Salad'),(110,1817,3,'2 Slices Gluten Free Bread, 2 Tbsp Peanut Butter, 1 Banana,2  Cups Milk, 1/2 Cup Hummus','3 Cups Salad, 5 Tomato Slices, 1 Cup Chicken, 1/2 Cup Qunioa, 2 Tbsp. Cottage Cheese','1 Fillet Salmon, 1 Potato, 1 Cup Green Beans'),(111,2427,0,'4 eggs, 2 Biscuits, Butter, Jelly, 2 Cups Milk','1 Cup Chicken, 1 Leaf Lettuce, 1 Slice Tomato, 1 Slize Cheese, 1 Tbsp mayo, 1 Apple, 1 Cup sweet Potato','1 Cup Fettucine, 1/2 Cup Sauce, 3 Oz Ground Beef, 2 Slices Bread, '),(112,2221,0,'1 Cup Corn Flakes, 1 Cup Milk, 1/2 Cup blueberries, 2 Slices Bread, 2 Tbsp Peanut Butter','2 Cups Turkey, 2 Slices Bread, 2 Tsp Mustard, 1 Leaf Lettuce, 1 Cup Green Beans, 1 Oz Almonds, 1 Banana','8 Oz Steak, 1 Cup Mashed Potatoes, 2 Stalks Broccoli'),(113,2822,0,'1 Cup Oats, 1 Cup Milk, 1 Banana, 1 Slice Bread, 2 Tbsp Peanut Butter','1.5 Cups Whole Wheat Fettuccine, 3/4 Cups Sauce, 4 Oz Ground Beef,  2 Cups Salad, 1 Cup Cheese ','1 Fillet Salmon, 1 Cup Brown Rice, 2 Baked Potatoes'),(114,1976,0,'1 Slice Bread, 1 Cup Avocado, 1 Egg, 1 Banana, 2 Tbsp Almonds, 1 Cup Yogurt, 1/2 Cup Blueberries, 1 Tsp. Honey','2 Cups Fettucine Alfredo, 2 Slice of Bread, 2 Slice Tomato, 2 Slice Cheese, 1 Oz Ground beef, 1 Cup Green Beans, ','5 Oz Steak, 1 Cup Brown Rice, 2 Tbsp Walnuts, 2 Cups Salad');
/*!40000 ALTER TABLE `diet_plans` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-12-03 23:20:30
