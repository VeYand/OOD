#ifndef SETTITLECOMMAND_H
#define SETTITLECOMMAND_H

#include <string>
#include <utility>
#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"

class SetTitleCommand final : public AbstractCommand
{
public:
	explicit SetTitleCommand(
		std::string &title,
		std::string newTitle
	): m_currentTitle(title),
	   m_newTitle(std::move(newTitle))
	{
	}

	void DoExecute() override
	{
		std::swap(m_currentTitle, m_newTitle);
	}

	void DoUnexecute() override
	{
		std::swap(m_newTitle, m_currentTitle);
	}

private:
	std::string &m_currentTitle;
	std::string m_newTitle;
};

#endif //SETTITLECOMMAND_H
