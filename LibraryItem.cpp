#include "LibraryItem.h"
int LibraryItem::nextLibItemID = 0;
LibraryItem::LibraryItem() {
        ifTaken = false;
        genre = Genre::g1;
        rating = 0.0;
    }
    int LibraryItem::get_ID() const{
        return ID;
    }
    double LibraryItem::get_rating() const {
        return rating;
    }
    String LibraryItem::get_publisher() const {
        return publisher;
    }
    Genre LibraryItem::get_genre() const {
        return genre;
    }
    String LibraryItem::get_description() const {
        return shortDescription;
    }
    String LibraryItem::get_isbn()const{
        return isbn;
    }
    void LibraryItem::set_ifTaken(const bool ifTaken) {

        this->ifTaken = ifTaken;
    }

