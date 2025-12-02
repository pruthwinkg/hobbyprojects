from sqlalchemy.orm import sessionmaker
from contextlib import contextmanager
from sqlalchemy import create_engine

# Define the database connection URL
DATABASE_URL = 'postgresql://postgres:postgres@postgres:5432/smarthome-db'

# Define a context manager to handle sessions
@contextmanager
def db_session_context():
    engine = create_engine(DATABASE_URL, echo=False, pool_size=10, max_overflow=20)
    Session = sessionmaker(bind=engine)
    
    session = Session()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()
