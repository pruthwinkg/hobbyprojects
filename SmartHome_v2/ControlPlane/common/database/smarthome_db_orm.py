from sqlalchemy import create_engine, Column, Integer, String, ForeignKey, JSON
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class Profile(Base):
    __tablename__ = 'profile'

    pid = Column(Integer, primary_key=True)
    name = Column(String(50))
    properties = Column(JSON)

class Users(Base):
    __tablename__ = 'users'

    uid = Column(Integer, primary_key=True)
    name = Column(String(50))
    hashed_password = Column(String(100))
    properties = Column(JSON)
    pid = Column(Integer, ForeignKey("profile.pid"))

    def to_dict(self):
        return {column.name: getattr(self, column.name) for column in self.__table__.columns}