#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY(117, "Превышена максимальная ёмкость таблицы лексем"),
		ERROR_ENTRY(118, "Текущий размер таблицы лексем привысил максимальное значение"),
		ERROR_ENTRY(119, "Строка отсутствует в таблице лексем"),
		ERROR_ENTRY(120, "Превышена максимальная ёмкость таблицы индетификаторов"),
		ERROR_ENTRY(121, "Текущий размер таблицы индетификаторов привысил максимальное значение"),
		ERROR_ENTRY(122, "Строка отсутствует в таблице индетификаторов"),
		ERROR_ENTRY(123, "Не удалось разобрать лексему"),
		ERROR_ENTRY(124, "Не удалось открыть файл"),
		ERROR_ENTRY(125, "Необъявленный идентификатор"),
		ERROR_ENTRY(126, "Отсутствует тип данных индентификатора"),
		ERROR_ENTRY(127, "Повторное объявление переменной"),
		ERROR_ENTRY(128, "Выход за разрешённые границы целого числа"),
		ERROR_ENTRY(129, "Отсутствует точка входа в программу"),
		ERROR_ENTRY(130, "Обнаружено несколько точек входа в программу"),
		ERROR_ENTRY(131, "Отсутствует закрывающая } в конструкции main"),
		ERROR_ENTRY(132, "Несоответствие количества парметров функции(процедуры)"),
		ERROR_ENTRY(133, "Несоответствие типов параметров функции(працедуры)"),
		ERROR_ENTRY_NODEF(134), ERROR_ENTRY_NODEF(135), 
		ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137),	ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139), 
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка в праметрах функции"),
		ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(605), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		ERROR error;
		if (id <= 0 || id > ERROR_MAX_ENTRY)
		{
			error.id = errors[0].id;
			sprintf_s(error.message, "%s", errors[0].message);
			return error;
		}
		else
		{
			error.id = errors[id].id;
			sprintf_s(error.message, "%s", errors[id].message);
			return error;
		}
	}

	ERROR geterrorin(int id, int line = -1, int col = -1) {
		ERROR error;
		if (id <= 0 || id > ERROR_MAX_ENTRY)
		{
			error.id = errors[0].id;
			sprintf_s(error.message, "%s", errors[0].message);
			error.inext.col = col;
			error.inext.line = line;
			return error;
		}
		else 
		{
			error.id = errors[id].id;
			sprintf_s(error.message, "%s", errors[id].message);
			error.inext.col = col;
			error.inext.line = line;
			return error;
		}
		
	}
};