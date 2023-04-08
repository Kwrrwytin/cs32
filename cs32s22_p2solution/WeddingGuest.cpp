#include "WeddingGuest.h"

WeddingGuest::WeddingGuest()
{
	head = tail = nullptr;
	numGuests = 0;
}

WeddingGuest::WeddingGuest(const WeddingGuest& p)
{
	if (p.head == nullptr) {
		head = tail = nullptr;
		numGuests = 0;
	}
	else {
		Node* iter = p.head;
		Node* curr = new Node();
		curr->firstName = iter->firstName;
		curr->lastName = iter->lastName;
		curr->info = iter->info;
		head = tail = curr;
		iter = iter->next;
		while (iter) {
			curr = new Node();
			curr->firstName = iter->firstName;
			curr->lastName = iter->lastName;
			curr->info = iter->info;
			tail->next = curr;
			curr->prev = tail;
			tail = curr;
			iter = iter->next;
		}
		head->prev = tail->next = nullptr;
		numGuests = p.numGuests;
	}
}

WeddingGuest::~WeddingGuest()
{
	Node* p = head;
	while (p) {
		Node* q = p->next;
		delete p;
		p = q;
	}
}

WeddingGuest& WeddingGuest::operator=(const WeddingGuest& p)
{
	WeddingGuest temp(p);
	Node* m = head;
	while (m) {
		Node* n = m->next;
		delete m;
		m = n;
	}
	if (temp.head == nullptr) {
		head = tail = nullptr;
		numGuests = 0;
	}
	else {
		Node* iter = temp.head;
		Node* curr = new Node();
		curr->firstName = iter->firstName;
		curr->lastName = iter->lastName;
		curr->info = iter->info;
		head = tail = curr;
		iter = iter->next;
		while (iter) {
			curr = new Node();
			curr->firstName = iter->firstName;
			curr->lastName = iter->lastName;
			curr->info = iter->info;
			tail->next = curr;
			curr->prev = tail;
			tail = curr;
			iter = iter->next;
		}
		head->prev = tail->next = nullptr;
		numGuests = temp.numGuests;
	}
	return *this;
}

bool WeddingGuest::noGuests() const
{
	if (head)
		return false;
	else
		return true;
}

int WeddingGuest::guestCount() const
{
	return numGuests;
}

bool WeddingGuest::inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
	Node* p = head;
	Node* targetGuest = nullptr;
	bool insertNewHead = false;
	if (p == nullptr) {
		Node* newGuest = new Node();
		newGuest->firstName = firstName;
		newGuest->lastName = lastName;
		newGuest->info = value;
		newGuest->prev = newGuest->next = nullptr;
		head = tail = newGuest;
		++numGuests;
		return true;
	}
	while (p) {
		if (p->lastName == lastName) {
			if (p->firstName == firstName)
				return false;
			else if (p->firstName > firstName) {
				if (p == head)	insertNewHead = true;
				else	targetGuest = p->prev;
				break;
			}
			else if (p->firstName < firstName) {
				if (p->next) {
					if (p->next->firstName > firstName)	{targetGuest = p; break;}
				}
				else	targetGuest = p;
			}
		}
		else if (p->lastName > lastName) {
			if (p == head)	insertNewHead = true;
			else	targetGuest = p->prev;
			break;
		}
		else if (p->lastName < lastName) {
			if (p->next) {
				if (p->next->lastName > lastName)	{targetGuest = p; break;}
			}
			else	targetGuest = p;
		}
		p = p->next;
	}

	Node* newGuest = new Node();
	newGuest->firstName = firstName;
	newGuest->lastName = lastName;
	newGuest->info = value;

	if (insertNewHead) {
		newGuest->next = p;
		newGuest->prev = nullptr;
		p->prev = newGuest;
		head = newGuest;
	}
	else {
		newGuest->next = targetGuest->next;
		newGuest->prev = targetGuest;
		if (targetGuest->next)	targetGuest->next->prev = newGuest;
		else	tail = newGuest;
		targetGuest->next = newGuest;
	}
	++numGuests;
	return true;
}

bool WeddingGuest::alterGuest(const std::string &firstName, const std::string &lastName, const GuestType& value)
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	{p->info = value; return true;}
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool WeddingGuest::inviteOrAlter(std::string firstName, std::string lastName, const GuestType& value)
{
	bool resChange = alterGuest(firstName, lastName, value);
	if (!resChange)	inviteGuest(firstName, lastName, value);
	return true;
}

bool WeddingGuest::crossGuestOff(const std::string& firstName, const std::string& lastName)
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName) {
			if (p == head && p == tail) {
				head = tail = nullptr;
			}
			else if (p == head) {
				head = p->next;
				head->prev = nullptr;
			}
			else if (p == tail) {
				tail = p->prev;
				tail->next = nullptr;
			}
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			delete p;
			--numGuests;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool WeddingGuest::invitedToTheWedding(const std::string firstName, const std::string lastName) const
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	return true;
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool WeddingGuest::matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	{value = p->info; return true;}
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType& value) const
{
	if (i >= 0 && i < numGuests) {
		Node* p = head;
		while (i) {
			p = p->next;
			--i;
		}
		firstName = p->firstName;
		lastName = p->lastName;
		value = p->info;
		return true;
	}
	else	return false;
}

void WeddingGuest::swapWeddingGuests(WeddingGuest& other)
{
	Node* temp = head;
	head = other.head;
	other.head = temp;

	temp = tail;
	tail = other.tail;
	other.tail = temp;

	int guestCount = numGuests;
	numGuests = other.numGuests;
	other.numGuests = guestCount;
}

bool joinGuests(const WeddingGuest& m1, const WeddingGuest& m2, WeddingGuest& result)
{
	WeddingGuest tempResult(m2);
	bool returnValue = true;
	for (int i = 0; i < m1.guestCount(); ++i) {
		std::string firstName, lastName;
		GuestType value, value_res;
		m1.verifyGuestOnTheList(i, firstName, lastName, value);
		if (tempResult.matchInvitedGuest(firstName, lastName, value_res)) {
			if (value_res == value)	continue;
			else	{tempResult.crossGuestOff(firstName, lastName); returnValue = false;}
		}
		else	tempResult.inviteGuest(firstName, lastName, value);
	}
	result = tempResult;
	return returnValue;
}

void attestGuests(const std::string& fsearch, const std::string& lsearch,
            const WeddingGuest& p1, WeddingGuest& result)
{
	if (fsearch == "*" && lsearch == "*")	{result = p1; return;}
	WeddingGuest tempResult;
	if (fsearch == "*") {
		for (int i = 0; i < p1.guestCount(); ++i) {
			std::string firstName, lastName;
			GuestType value;
			p1.verifyGuestOnTheList(i, firstName, lastName, value);
			if (lastName == lsearch)	tempResult.inviteGuest(firstName, lastName, value);
		}
	}
	else if (lsearch == "*") {
		for (int i = 0; i < p1.guestCount(); ++i) {
			std::string firstName, lastName;
			GuestType value;
			p1.verifyGuestOnTheList(i, firstName, lastName, value);
			if (firstName == fsearch)	tempResult.inviteGuest(firstName, lastName, value);
		}
	}
	else {
		GuestType value;
		if (p1.matchInvitedGuest(fsearch, lsearch, value))	tempResult.inviteGuest(fsearch, lsearch, value);
	}
	result = tempResult;
}
